#!/usr/bin/env python3

import rospy
from std_msgs.msg import String
from bluepy.btle import Scanner, DefaultDelegate

DEVICE_MAC = 'a0:b7:65:5a:e5:b2'

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

    def handleDiscovery(self, dev, isNewDev, isNewData):
        if dev.addr == DEVICE_MAC:
            rssi = dev.rssi
            distance = calculate_distance(rssi)
            rssi_msg = String(data=f"Device {dev.addr} Distance: {distance} meters, RSSI = {rssi} dBm")
            rssi_publisher.publish(rssi_msg)

def calculate_distance(rssi):
    tx_power = -59  # Adjust this value based on your specific setup
    n = 2.0  # Path loss exponent (use 2.0 for free space)

    ratio = rssi * 1.0 / tx_power
    distance = (10 ** ((tx_power - rssi) / (10 * n)))  # Distance in meters
    return distance

if __name__ == '__main__':
    rospy.init_node('car_publisher')
    rssi_publisher = rospy.Publisher('ble_rssi', String, queue_size=10)
    scanner = Scanner().withDelegate(ScanDelegate())

    print("Scanning for ESP32...")
    try:
        while not rospy.is_shutdown():
            devices = scanner.scan(1.0)
    except KeyboardInterrupt:
        pass
