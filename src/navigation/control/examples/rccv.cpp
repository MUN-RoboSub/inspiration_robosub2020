#include "rc_communicator.h"
#include "global_data.h"
#include "rccv.h"

/*
  This is an example file. It demonstrates how to combine input from computer vision and
  rc control. The function tells the sub to move if the finalgate program is publishing
  bounding box coordinates.
  "finalgateCoords" was declared in main.cpp, and is assigned a value in the finalgate
  callback function. The callback function executes when the subscriber is updated.
 */

void rc_if_cv(int channel, int pwm) {
  if(!finalgateCoords.empty()){
    rc_raw(channel, pwm);
  }
}
