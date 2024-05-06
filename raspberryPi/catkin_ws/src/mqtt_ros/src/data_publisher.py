#!/usr/bin/env python3

import rospy
from bluepy.btle import Scanner, DefaultDelegate
import serial
from std_msgs.msg import String

DEVICE_MAC = 'a0:b7:65:5a:e5:b2'  # ESP32의 Blutooth MAC 주소
BAUD_RATE = 9600  

# rssi 및 거리에 대한 매핑 범위 (0~255 범위로 매핑하기 위한 변수)
#RSSI_MIN = -100
#QRSSI_MAX = 0
#DISTANCE_MIN = 0.0
#DISTANCE_MAX = 10.0

# RSSI 값을 필터링하기 위한 칼만 필터 클래스 정의
class KalmanFilter():
    def __init__(self, processNoise=0.005, measurementNoise=20):
        self.isInitialized = False  # 칼만 필터 초기화 여부를 나타내는 플래그 설정
        self.processNoise = processNoise  # 프로세스 노이즈: 예측 오차를 나타내는 값
        self.measurementNoise = measurementNoise  # 측정 노이즈: 측정 오차를 나타내는 값
        self.predictedRSSI = 0  # 예측된 RSSI값
        self.errorCovariance = 0  # 오차 공분산: 예측 오차의 정도를 나타내는 값

    def filtering(self, rssi):
        # 칼만 필터가 초기화되지 않은 경우
        if not self.isInitialized: 
            self.isInitialized = True  
            priorRSSI = rssi  
            priorErrorCovariance = 1  
         # 칼만 필터가 이미 초기화되어 있는 경우    
        else: 
            priorRSSI = self.predictedRSSI  
            priorErrorCovariance = self.errorCovariance + self.processNoise 

        kalmanGain = priorErrorCovariance / (priorErrorCovariance + self.measurementNoise)  # 칼만 이득 계산
        self.predictedRSSI = priorRSSI + (kalmanGain * (rssi - priorRSSI))  # 예측된 RSSI값 계산
        self.errorCovariance = (1 - kalmanGain) * priorErrorCovariance  # 오차 공분산 계산

        return self.predictedRSSI  # 필터링된 예측 RSSI 값을 반환

# 디바이스 스캔 후 esp32 보드를 처리하기 위한 클래스 정의
class ScanDelegate(DefaultDelegate):
    def __init__(self, ser):
        DefaultDelegate.__init__(self)
        self.ser = ser  

    # 스캔된 장치가 ESP32 보드의 mac 주소와 같다면 디바이스의 RSSI값 계산
    def handleDiscovery(self, dev, isNewDev, isNewData):
        if dev.addr == DEVICE_MAC:  
            rssi = dev.rssi 
            # RSSI가 -40dbm 이상이면 스캔 종료 후 
            if rssi >= -40:  
                rospy.loginfo("rssi scanning stop")  
                rospy.signal_shutdown("rssi scanning stop")  
                return
            distance = calculate_distance(rssi)  
            data_to_send = f"{rssi},{distance}\n" 
            self.ser.write(data_to_send.encode()) 

# RSSI 값을 거리로 변환하는 함수 
def calculate_distance(rssi):
    tx_power = -59  # ESP32의 신호 출력 설정에 따라 값 설정 (단위: dBm)
    n = 2.0  # 경로 손실 지수 (2.0은 자유 공간에 가까운 환경을 가정한 값)

    ratio = rssi * 1.0 / tx_power
    distance = (10 ** ((tx_power - rssi) / (10 * n)))  # 단위: 미터
    return distance  

#def map_value(value, in_min, in_max, out_min, out_max):
    #return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# 블루투스 장치 데이터를 ROS로 발행하는 함수
def rssi_publisher():
    ser = serial.Serial('/dev/ttyACM0', BAUD_RATE) 

    scanner = Scanner().withDelegate(ScanDelegate(ser))  # 블루투스 스캐너 설정

    rospy.init_node('data_publisher', anonymous=True)  # ROS 노드 초기화
    rssi_pub = rospy.Publisher('rssi_data', String, queue_size=10)  # ROS 토픽과 메시지 타입 설정

    kalman_filter = KalmanFilter()  # 칼만 필터 객체 생성

    print("호출벨을 스캔중입니다...")
    try:
        while not rospy.is_shutdown(): 
            devices = scanner.scan(0.1)  
            for dev in devices:
                if dev.addr == DEVICE_MAC:
                    rssi = dev.rssi  
                    if rssi >= -40: 
                        rospy.loginfo("rssi scanning stop")
                        rospy.signal_shutdown("rssi scanning stop")
                        break
                    filtered_rssi = kalman_filter.filtering(rssi)  
                    distance = calculate_distance(filtered_rssi) 
                    data_to_send = f"{filtered_rssi},{distance}\n" 
                    ser.write(data_to_send.encode()) 
                    rospy.loginfo(f"Data sent: {data_to_send}")  
                    rssi_pub.publish(data_to_send)  
    except rospy.ROSInterruptException:
        pass
    ser.close()  

if __name__ == '__main__':
    try:
        rssi_publisher() 
    except rospy.ROSInterruptException:
        pass