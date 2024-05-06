#!/usr/bin/env python3

import rospy
import serial
from detection_msgs.msg import BoundingBoxes

ser = serial.Serial('/dev/ttyUSB0', 9600)  
tracked_obj_name = None  # 추적되는 객체의 이름을 저장
tracked_start_time = None  # 해당 객체의 추적 시간을 저장

# 시리얼 통신을 통해 객체 이름을 아두이노로 보내는 함수
def send_to_arduino(obj_name):
    ser.write(obj_name.encode()) 

# BoundingBoxes 메시지를 수신하는 ros 토픽의 콜백 함수
def callback(data):
    global tracked_obj_name, tracked_start_time

    for obj in data.bounding_boxes:
        obj_name = obj.Class  # 감지된 객체의 이름 저장
        print(f"Detected object: {obj_name}")

        if obj_name != tracked_obj_name: 
            tracked_obj_name = obj_name  
            tracked_start_time = rospy.Time.now()  

        # 3초이상 같은 객체가 인식되면 send_to_arduino() 함수를 호출하여 아두이노로 데이터 전송
        if (rospy.Time.now() - tracked_start_time).to_sec() >= 3.0:
            send_to_arduino(obj_name)
            tracked_start_time = rospy.Time.now()

def detect_node():
    rospy.init_node("detection_name", anonymous=True)  # ros 노드 초기화
    rospy.Subscriber("yolov5/detections", BoundingBoxes, callback)  # yolov5/detections 토픽에서 BoundingBoxes 메시지를 구독하며 콜백 함수 실행
    rospy.spin()

# detect_node() 함수를 호출하여 노드를 실행
if __name__ == "__main__":
    try:
        detect_node()
    except rospy.ROSInterruptException:
        pass