#ifndef MAINPP_H_
#define MAINPP_H_

#ifdef __cplusplus

#include "ros.h"
#include "std_msgs/Int16MultiArray.h"
#include <std_msgs/String.h>

extern "C" {

#endif

void pub_to_ros();
void ros_setup();
void ros_loop();
#ifdef __cplusplus
}

#endif

#endif /* MAINPP_H_ */
