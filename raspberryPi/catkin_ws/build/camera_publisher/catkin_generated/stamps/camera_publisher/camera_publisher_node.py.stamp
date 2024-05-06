#!/usr/bin/env python3

import cv2
import rospy
from cv_bridge import CvBridge
from sensor_msgs.msg import Image

def main():
    # Initialize the ROS node
    rospy.init_node('camera_publisher', anonymous=True)

    # Initialize the publisher
    image_pub = rospy.Publisher('camera/image', Image, queue_size=10)

    # Initialize the OpenCV video capture
    cap = cv2.VideoCapture(0)

    # Check if the camera is opened successfully
    if not cap.isOpened():
        print("Error: Could not open camera.")
        return

    # Set camera resolution
    cap.set(3, 600)  # Width
    cap.set(4, 400)  # Height

    # Initialize CvBridge
    bridge = CvBridge()

    while not rospy.is_shutdown():
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Convert the frame to ROS message
        ros_image = bridge.cv2_to_imgmsg(frame, "bgr8")

        # Publish the ROS image message
        image_pub.publish(ros_image)

        # Display the frame locally (optional)
        cv2.imshow('Camera Test', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the camera and close OpenCV windows
    cap.release()
    cv2.destroyAllWindows()

if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass
