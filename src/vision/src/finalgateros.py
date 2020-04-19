#!/usr/bin/env python

import rospy
from navigation.msg import CVarray

import cv2
import numpy as np
import math

'''
adopted from finalgate1.py, adapted to work with ROS
original author: pahels
'''

class GateDetector(object):
    
    def __init__(self):
        self.finalgate_pub = rospy.Publisher('finalgate_cv', CVarray, queue_size=10)
        self.video = cv2.VideoCapture("cleargate.mp4")
            
def main():
    gate_detector = GateDetector()
    rospy.init_node('cv_publisher', anonymous=True)

    # downscale the image
    scale = 0.5

    # minimize false detections by eliminating contours less than a percentage of the image
    area_threshold = 0

    ret, orig_frame = gate_detector.video.read()
    width = orig_frame.shape[0]
    height = orig_frame.shape[1]
    dim = (int(scale*height), int(scale*width))

    while not rospy.is_shutdown():
        ret, orig_frame = gate_detector.video.read()
        if not ret:
		break

	orig_frame = cv2.resize(orig_frame, dim, interpolation = cv2.INTER_AREA)
	frame = cv2.GaussianBlur(orig_frame, (5, 5), 0)
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	
	mask0 = cv2.inRange(hsv,(0, 0, 20), (25, 255, 255) )
	mask1 = cv2.inRange(hsv,(160, 0, 20), (179, 255, 255) )
	# join masks
	mask = mask0 + mask1

	ret, thresh = cv2.threshold(mask, 127, 255,0)
    #Erosions and dilations
    #erosions are apploed to reduce the size of foreground objects
	kernel = np.ones((3,3),np.uint8)
	eroded = cv2.erode(thresh, kernel, iterations=1)	
	dilated = cv2.dilate(eroded, kernel, iterations=1)

	_, cnts,hierarchy = cv2.findContours(dilated,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:3]

	boundingBoxes = np.empty((0, 4), float)
	if len(cnts) > 0:

		M = cv2.moments(cnts[0])
		for c in cnts:
			rect = cv2.minAreaRect(c)
			
			# the order of the box points: bottom left, top left, top right,
			# bottom right
			box = cv2.boxPoints(rect)
			box = np.int0(box)

			cv2.drawContours(orig_frame, [box], 0, (0, 0, 255), 2)
			cv2.imshow("bounding rectangle",orig_frame)

                        # print and publish the information to ROS
                        box = box.flatten()
                        print(box)
                        box = box.tolist()
                        gate_detector.finalgate_pub.publish(box)
        
	key = cv2.waitKey(1)
	if key == 27:
		break
    
    gate_detector.video.release()
    cv2.destroyAllWindows()
    
if __name__ == "__main__":
    main()
