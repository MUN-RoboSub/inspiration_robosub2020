# inspiration_robosub2020

## About
This is [Team Inspiration](https://team11128.wixsite.com/main)'s repository for the (now-cancelled) 2020 [RoboSub](https://robonation.org/programs/robosub/) season.

## Setup and Dependencies
The AUV's software has been split into two primary packages:
* Navigation (navigation and movement control)
* Vision (computer vision)

### Installing the program and its dependencies

In order to run this software on a computer/AUV, follow the steps below (this assumes that you are using Ubuntu):
1. Obtain the software in this repository

   ```git clone https://github.com/InspirationRobotics```

2. Install a version of [ROS](http://wiki.ros.org/ROS/Installation) that is appropriate to your version of Ubuntu
3. [Install MAVROS](https://dev.px4.io/v1.9.0/en/ros/mavros_installation.html)

### Building and running the program
1. Build and install the program

   ```catkin_make install```

2. Source the setup file

   ```source devel/setup.bash```

3. Start roscore

   ```roscore```

4. Start MAVROS. Note: if you are using SITL, you will have to add the address of the simulated vehicle, ex: "fcu_url:=0.0.0.0:14550"

   ```roslaunch mavros apm.launch```

5. **(optional)** Arm the vehicle if you aren't doing so within the program

   ```rosrun mavros mavsafety arm```

6. Run the program

   ```rosrun navigation main```

### Additional notes

* If you intend to run the vision programs then you must install their dependencies via `pip` or some other method