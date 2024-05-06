import cv2
import rospy
from sensor_msgs.msg import CompressedImage

def main():
    # ros 노드 초기화
    rospy.init_node('camera_publisher', anonymous=True)
	# 퍼블리셔 초기화 -> CompressedImage: 이미지를 압축해서 전송
    image_pub = rospy.Publisher('/camera_image', CompressedImage, queue_size=10)
	# 비디오캡처 초기화
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("카메라 연결 실패")
        return

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 600) # width
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 400) # height

    while not rospy.is_shutdown():
		# 프레임 단위로 캡처
        ret, frame = cap.read()
        # JPEG 형식으로 이미지 압축 -> imencode: 이미지를 JPEG 형식으로 압축해주는 함수
        encode_param = [int(cv2.IMWRITE_JPEG_QUALITY), 90]
        _, jpg_image = cv2.imencode('.jpg', frame, encode_param)
        # 프레임을 CompressedImage 메시지로 변환하여 전송
        ros_image = CompressedImage()
        ros_image.header.stamp = rospy.Time.now()
		# 이미지를 JPEG 형식으로 설정
        ros_image.format = "jpeg"
        ros_image.data = jpg_image.tostring()
		# ros 이미지 메시지를 퍼블리셔로 설정
        image_pub.publish(ros_image)
				
        cv2.imshow('Camera Test', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass