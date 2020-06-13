import sys
import rospy
from navigation.msg import CVarray

try:
    file = open(sys.argv[1], "r")
except:
    print("please choose a valid file to read from\nusage: python gate_dummy.py [file]")
    sys.exit(1)

pub = rospy.Publisher('gate_dummy', CVarray, queue_size=10)
rospy.init_node('gate_dummy', anonymous=True)
rate = rospy.Rate(10)

for ln in file:
    strippedln = ln.strip()
    convertedln = list(map(int, strippedln.split(',')))

    # print(convertedln)
    pub.publish(convertedln)
    rate.sleep()
