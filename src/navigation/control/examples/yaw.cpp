#include "control/rc_communicator.h"
#include "control/yaw.h"

/*
  This is an example file. It is a demonstration of how to build navigation functions using rc_communicator
  1) include "mavros_communicator.h"
  2) include this file's header file
 */
void yaw() {
  rc_raw(4, 1900);
}
