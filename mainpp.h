#ifndef MAINPP_H_
#define MAINPP_H_

#include "ros.h"
#include <std_msgs/Int16MultiArray.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

void pub_to_ros();
void ros_setup();
void ros_loop();
void hand_shake();
void pub_to_start();
#endif /* MAINPP_H_  */
