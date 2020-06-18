import rospy
from std_msgs.msg import String

import subprocess

proc = subprocess.Popen(["./dummy_start_vu_capture.sh"], stdout=subprocess.PIPE)

def talker():
    pub = rospy.Publisher('vuforia_data', String, queue_size=10)
    rospy.init_node('vuforia_reader', anonymous=True)
    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        line = proc.stdout.readline()
        if not line:
            break
        
        pub.publish(line)
        rate.sleep()

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
