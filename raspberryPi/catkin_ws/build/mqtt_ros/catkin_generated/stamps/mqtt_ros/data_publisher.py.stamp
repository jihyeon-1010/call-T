#!/usr/bin/env python3

import rospy
from bluepy.btle import Scanner, DefaultDelegate
import serial
from std_msgs.msg import String

DEVICE_MAC = 'a0:b7:65:5a:e5:b2'  # ESP32의 Blutooth MAC 주소
BAUD_RATE = 9600  # 아두이노와 시리얼 통신 속도

# rssi 및 거리에 대한 매핑 범위 (0~255 범위로 매핑하기 위한 변수)
#RSSI_MIN = -100
#QRSSI_MAX = 0
#DISTANCE_MIN = 0.0
#DISTANCE_MAX = 10.0

# 칼만 필터 클래스 정의
class KalmanFilter():
    def __init__(self, processNoise=0.005, measurementNoise=20):
        self.isInitialized = False
        self.processNoise = processNoise
        self.measurementNoise = measurementNoise
        self.predictedRSSI = 0
        self.errorCovariance = 0

    def filtering(self, rssi):
        # 칼만 필터링을 위한 함수 정의
        if not self.isInitialized:
            self.isInitialized = True
            priorRSSI = rssi
            priorErrorCovariance = 1
        else:
            priorRSSI = self.predictedRSSI
            priorErrorCovariance = self.errorCovariance + self.processNoise

        kalmanGain = priorErrorCovariance / (priorErrorCovariance + self.measurementNoise)
        self.predictedRSSI = priorRSSI + (kalmanGain * (rssi - priorRSSI))
        self.errorCovariance = (1 - kalmanGain) * priorErrorCovariance

        return self.predictedRSSI

# ScanDelegate 클래스 정의
class ScanDelegate(DefaultDelegate):
    def __init__(self, ser):
        DefaultDelegate.__init__(self)
        self.ser = ser  # 시리얼 통신 객체를 저장

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if dev.addr == DEVICE_MAC:
            rssi = dev.rssi
            # rssi가 -40dbm 이상이면 파이썬 파일 종료
            if rssi >= -40: 
                rospy.loginfo("rssi scanning stop")
                rospy.signal_shutdown("rssi scanning stop")
                return
            distance = calculate_distance(rssi)
            data_to_send = f"{rssi},{distance}\n"
            self.ser.write(data_to_send.encode())

# RSSI를 거리로 변환하는 함수 정의
def calculate_distance(rssi):
    tx_power = -59
    n = 2.0

    ratio = rssi * 1.0 / tx_power
    distance = (10 ** ((tx_power - rssi) / (10 * n)))
    return distance

#def map_value(value, in_min, in_max, out_min, out_max):
    #return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

# 블루투스 장치를 스캔하고 데이터를 ROS로 게시하는 함수
def rssi_publisher():
    ser = serial.Serial('/dev/ttyACM0', BAUD_RATE)  # 아두이노와 시리얼 통신 설정

    scanner = Scanner().withDelegate(ScanDelegate(ser))  # 블루투스 스캐너 설정

    rospy.init_node('data_publisher', anonymous=True)  # ROS 노드 초기화
    rssi_pub = rospy.Publisher('rssi_data', String, queue_size=10)  # ROS 토픽과 메시지 타입 설정

    kalman_filter = KalmanFilter()  # 칼만 필터 객체 생성

    print("호출벨을 스캔중입니다...")
    try:
        while not rospy.is_shutdown():
            devices = scanner.scan(0.1)  # 블루투스 장치 스캔
            for dev in devices:
                if dev.addr == DEVICE_MAC:
                    rssi = dev.rssi
                    if rssi >= -40:
                        rospy.loginfo("rssi scanning stop")
                        rospy.signal_shutdown("rssi scanning stop")
                        break
                    filtered_rssi = kalman_filter.filtering(rssi)  # 칼만 필터로 RSSI 필터링
                    distance = calculate_distance(filtered_rssi)  # 거리 계산
                    data_to_send = f"{filtered_rssi},{distance}\n"  # 데이터 포맷 설정
                    ser.write(data_to_send.encode())  # 시리얼로 데이터 전송
                    rospy.loginfo(f"Data sent: {data_to_send}")  # 로그에 데이터 출력
                    rssi_pub.publish(data_to_send)  # ROS로 데이터 발행
    except rospy.ROSInterruptException:
        pass
    ser.close()  # 시리얼 연결 닫기

if __name__ == '__main__':
    try:
        rssi_publisher()  # 메인 함수 실행
    except rospy.ROSInterruptException:
        pass