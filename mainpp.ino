#include <std_msgs/String.h>
#include "servocontrol.h"
#include <HardwareSerial.h>
#include "mainpp.h"

ros::NodeHandle nh;
std_msgs::Int16MultiArray feedback;
ros::Subscriber<std_msgs::String> sub("mission0", cake_callback);
ros::Publisher pub("donefullness0", &feedback);
extern int b_bool, y_bool, p_bool, h_bool;
extern char hole[4];
extern short int mission_array[5];
extern int vacuum, vacuumservo;
extern int unload_cherry;
void cake_callback(const std_msgs::String &msg) {

  //  std::string str = msg.data; // string data
  if (msg.data[0] == 'b' || msg.data[0] == 'y' || msg.data[0] == 'p') {
    mission_array[(size_t)(msg.data[1] - '0' + 1)] = 1;
    temp_pub = 1;
    if (msg.data[1] == '0') {
      servo_angle[0] = angle_control_1(1);
    } else if (msg.data[1] == '1') {
      servo_angle[1] = angle_control_2(1);
    } else if (msg.data[1] == '2') {
      servo_angle[2] = angle_control_3(1);
    } else if (msg.data[1] == '3') {
      servo_angle[3] = angle_control_4(1);
    }
    mission_array[0] = 0;
  } else if (msg.data[0] == 'c') {
    //    mission_array[(size_t) (msg.data[1] - '0' + 1)] = 1;
    temp_pub = 0;
    if (msg.data[1] == '0') {
      servo_angle[0] = angle_control_1(2);
    } else if (msg.data[1] == '1') {
      servo_angle[1] = angle_control_2(2);
      temp_pub = 0;
    } else if (msg.data[1] == '2') {
      servo_angle[2] = angle_control_3(2);
    } else if (msg.data[1] == '3') {
      servo_angle[3] = angle_control_4(2);
    }
    mission_array[0] = 0;
  } else if (msg.data[0] == 'o') {
    vacuumservo=0;
    mission_array[(size_t)(msg.data[1] - '0' + 1)] = 0;
    temp_pub = 0;
    if (msg.data[1] == '0') {
      servo_angle[0] = angle_control_1(1);
    } else if (msg.data[1] == '1') {
      servo_angle[1] = angle_control_2(1);
    } else if (msg.data[1] == '2') {    
      servo_angle[2] = angle_control_3(1);
    } else if (msg.data[1] == '3') {
      servo_angle[3] = angle_control_4(1);
    }
    mission_array[0] = 0;
  } else if (msg.data[0] == 'h') {
    temp_pub = 1;
    servo_angle[0] = angle_control_1(2);
    servo_angle[1] = angle_control_2(2);
    servo_angle[2] = angle_control_3(2);
    servo_angle[3] = angle_control_4(2);
    vacuumservo=1;
    mission_array[0] = 0;
  } else if (msg.data[0] == 's') {
    v_temp=0;
    vacuum = 1;
    temp_pub = 0;
    mission_array[0] = 0;
    if (msg.data[1] == '0' || msg.data[1] == '1' || msg.data[1] == '4'||msg.data[1]=='3')
      vacuumservo = 1;
    else if (msg.data[1] == '2' || msg.data[1] == '5')
      vacuumservo = 2;

  } else if (msg.data[0] == 'v') {
    vacuum = 2;
    temp_pub = 0;
    mission_array[0] = 0;

  } else if (msg.data[0] == 'u') {
    unload_cherry = 1;
    temp_pub = 1;
    mission_array[0] = 0;
  }
}
void ros_setup() {
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
}
void ros_loop() {
  nh.spinOnce();
}
void pub_to_ros() {

  feedback.data_length = 5;
  feedback.data = mission_array;
  //  feedback.data[5] = tower_step;

  pub.publish(&feedback);
  delay(100);
}