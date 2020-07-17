import cv2
import numpy as np
import math
import time
#from nms import non_max_suppression_fast
#import navigation/nav_interface


video = cv2.VideoCapture("SpaWarsGate3.mov")
#video = cv2.VideoCapture("gateC.mp4")
#video = cv2.VideoCapture("gateB.mp4")
#video = cv2.VideoCapture(0)

# Downscale the image to a reasonable size to reduce compute
scale = 1


# Minimize false detects by eliminating contours less than a percentage of the image
area_threshold = 0.01
croppedPixels = 150

ret, orig_frame = video.read()
width = orig_frame.shape[0]
height = orig_frame.shape[1] - croppedPixels
dim = (int(scale*height), int(scale*width))

while (True):

	ret, orig_frame = video.read()
	if not ret:
		break

	#ropped = orig_frame[croppedPixels:, :]
	#cv2.imshow("cropped", cropped)
 
	orig_frame = cv2.resize(orig_frame, dim, interpolation = cv2.INTER_AREA)
	frame = cv2.GaussianBlur(orig_frame, (5, 5), 0)
	hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
	
	mask0 = cv2.inRange(hsv,(0, 10, 10), (25, 255, 255) )
	mask1 = cv2.inRange(hsv,(160, 10, 10), (179, 255, 255) )
	# join masks
	mask = mask0 + mask1
	

	ret, thresh = cv2.threshold(mask, 127, 255,0)
 	#Erosions and dilations
 	#erosions are apploed to reduce the size of foreground objects
	kernel = np.ones((3,3),np.uint8)
	eroded = cv2.erode(thresh, kernel, iterations=0)	
	dilated = cv2.dilate(eroded, kernel, iterations=3) 
	#cv2.imshow("dilated", dilated)
	#cv2.waitKey(0)
	#cv2.imshow("Edged", edged)
 
	dst = cv2.equalizeHist(dilated)
    
	cv2.imshow("equilized", dst)

	cnts,hierarchy = cv2.findContours(dilated,cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	#cv2.drawContours(orig_frame, cnts, -1, (0, 255, 0), 3)
	cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:60]
    
    

	boundingBoxes = np.empty((0, 4), float)
	if len(cnts) > 0:

		M = cv2.moments(cnts[0])
		for c in cnts:
			rect = cv2.minAreaRect(c)
			#print("rect: {}".format(rect))

			# the order of the box points: bottom left, top left, top right,
			# bottom right
			box = cv2.boxPoints(rect)
			box = np.int0(box)

			#print("bounding box: {}".format(box))
			cv2.drawContours(orig_frame, [box], 0, (0, 0, 255), 2)
			#x,y,w,h = cv2.boundingRect(c)

			#boundingBoxes = np.append(boundingBoxes, np.array([[x,y,x+w,y+h]]), axis = 0)
			#cv2.rectangle(orig_frame,(x,y), (x+w, y+h), (255,0,0), 2)
			cv2.imshow("bounding rectangle",orig_frame)
			cv2.waitKey(0)

			#print(str(x/width) + " " + str(y/height) + " " + str((x+w)/width) + " " +  str((y+h)/height))

			box0 = (box[0])
			#print(box0[0]/width)
			#print(box0[1]/height)

			box1 = (box[1])
			#print(box1[0]/width)
			#print(box0[1]/height)

			box2 = (box[2])
			#print(box2[0]/width)
			#print(box2[1]/height)

			box3 = (box[3])
			#print(box3[0]/width)
			#print(box3[1]/height)

			boxSizeThreshold = 10

			if (box1[1]-box0[1])*(box3[0]-box0[0] > boxSizeThreshold ):
			#calculating middle point of box
				boxX = ((box1[0]+box2[0])/2)
				boxY = ((box2[1]+box3[1])/2)

				print("X", boxX, "Y", boxY)
	   
			else:
				boxX = -1
				boxY = -1
				print("no gate found")

		#passing the valuesc
		#nav_i  = nav_interface.Nav_send_intf("192.168.1.22", 5005, 'cv_nav_log', logging.INFO)
		#nav_i.send_cv_data(0, boxX, boxY, 0, 0, 0, 0, 0, 0, 0)

		time.sleep(.01)

		#cv_gate_data_json = {}
		#cv_gate_data_json['x'] = boxX
		#cv_gate_data_json['y'] = boxY

	# perform non-maximum suppression on the bounding boxes
	#pick = non_max_suppression_fast(boundingBoxes, 0.1)
	#print ("[x] after applying non-maximum, %d bounding boxes" % (len(pick)))

	# loop over the picked bounding boxes and draw them
	#for (startX, startY, endX, endY) in pick:
	#	cv2.rectangle(frame, (startX, startY), (endX, endY), (255, 255, 255), 2)

	# display the images
	#cv2.imshow("Original", orig)
	#cv2.imshow("After NMS", frame)
	#cv2.waitKey(0)

	key = cv2.waitKey(1)
	if key == 27:
		break

video.release()
cv2.destroyAllWindows()

