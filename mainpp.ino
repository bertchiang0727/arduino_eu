#include "servocontrol.h"
#include <HardwareSerial.h>
#include "mainpp.h"
#include "string.h"

ros::NodeHandle nh;
std_msgs::Int16MultiArray feedback;
std_msgs::String check;
std_msgs::Bool start; 
ros::Subscriber<std_msgs::String> sub("mission0", cake_callback);
ros::Subscriber<std_msgs::Int16MultiArray> sub1("hand_door0", door_def);
ros::Publisher pub("donefullness0", &feedback);
ros::Publisher pub1("handshaker0", &check);
ros::Publisher pub2("startornot", &start);
extern int b_bool, y_bool, p_bool, h_bool, debounce;
extern char hole[4];
extern short int mission_array[5];
extern int vacuum, vacuumservo;
extern int unload_cherry, k_temp, unplug;
int temp = 0;
String handshake = "";
void cake_callback(const std_msgs::String &msg) {
  handshake = msg.data;
  //  std::string str = msg.data; // string data
  if ((msg.data[0] == 'b' && temp != 1) || (msg.data[0] == 'y' && temp != 2) || (msg.data[0] == 'p' && temp != 3)) {
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
    if (msg.data[0] == 'b') temp = 1;
    else if (msg.data[0] == 'y') temp = 2;
    else if (msg.data[0] == 'p') temp = 3;
  } else if (msg.data[0] == 'c') {
    //    mission_array[(size_t) (msg.data[1] - '0' + 1)] = 1;
    temp_pub = 0;
    if (msg.data[1] == '0' && temp != 4) {
      servo_angle[0] = angle_control_1(2);
      temp = 4;
    } else if (msg.data[1] == '1' && temp != 5) {
      servo_angle[1] = angle_control_2(2);
      temp = 5;
    } else if (msg.data[1] == '2' && temp != 6) {
      servo_angle[2] = angle_control_3(2);//
      temp = 6;
    } else if (msg.data[1] == '3' && temp != 7) {
      servo_angle[3] = angle_control_4(2);
      temp = 7;
    }
    mission_array[0] = 0;

  } else if (msg.data[0] == 'o'||msg.data[0] == 't') {
    vacuumservo = 0;
    mission_array[(size_t)(msg.data[1] - '0' + 1)] = 0;
    temp_pub = 0;
    if (msg.data[1] == '0' && temp != 8) {
      servo_angle[0] = angle_control_1(1);
      temp = 8;
    } else if (msg.data[1] == '1' && temp != 9) {
      servo_angle[1] = angle_control_2(1);
      temp = 9;
    } else if (msg.data[1] == '2' && temp != 10) {
      servo_angle[2] = angle_control_3(1);
      temp = 10;
    } else if (msg.data[1] == '3' && temp != 11) {
      servo_angle[3] = angle_control_4(1);
      temp = 11;
    }
    mission_array[0] = 0;
  } else if (msg.data[0] == 'h' && temp != 12) {
    if(msg.data[1]=='0'){
      temp_pub=1;
    servo_angle[0] = angle_control_1(2);
    servo_angle[1] = angle_control_2(2);
    servo_angle[2] = angle_control_3(2);
    servo_angle[3] = angle_control_4(2);
    vacuumservo=3;
    mission_array[0]=0;
    temp=12;
    }
    else if(msg.data[1]=='3'){
temp_pub = 1;
    servo_angle[0] = angle_control_1(3);
    servo_angle[1] = angle_control_2(3);
    servo_angle[2] = angle_control_3(3);
    servo_angle[3] = angle_control_4(3);
    vacuumservo = 3;
    mission_array[0] = 0;
    temp = 12;
    }
    
  } else if (msg.data[0] == 's' && temp != 13) {
    v_temp = 0;
    vacuum = 1;
    temp_pub = 0;
    mission_array[0] = 0;
    if (msg.data[1] == '0' || msg.data[1] == '1' || msg.data[1] == '3' || msg.data[1] == '5')
      vacuumservo = 1;
    else if (msg.data[1] == '2' || msg.data[1] == '4')
      vacuumservo = 2;
    // else if(msg.data[1] == '4') vacuumservo = 4;
    temp = 13;
  } else if (msg.data[0] == 'v' && temp != 14) {
    vacuum = 2;
    temp_pub = 0;
    mission_array[0] = 0;
    vacuumservo = 3;
    temp = 14;
  } else if (msg.data[0] == 'u' && temp != 15) {
    unload_cherry = 1;
    temp_pub = 1;
    mission_array[0] = 0;
    temp = 15;
  } else if (msg.data[0] == 'f') {
    temp_pub = 1;
    mission_array[0] = 0;
    servo_angle[0] = 0;
    servo_angle[1] = 0;
    servo_angle[2] = 0;
    servo_angle[3] = 0;
    vacuumservo = 4;
    unload_cherry = 3;
  }
}
void door_def(const std_msgs::Int16MultiArray &msg1) {

  for (int i = 0; i < 4; i++) {
    if (msg1.data[i] == 1 && servo_angle[i] < 1430 && servo_angle[i] > 1350 && servo_angle[i] != 1380) {

      servo_angle[i] = 1375;
      // if (servo_angle[1] == 1384) servo_angle[1] = 1379;
      // if (servo_angle[2] == 1400) servo_angle[2] = 1385;
      k_temp = 1;
    }
    if (msg1.data[i] == 0 && servo_angle[i] < 1430 && servo_angle[i] > 1350 && servo_angle[i] != 1425) {
      servo_angle[i] = 1400;
      k_temp = 1;
    }
  }
}
void pub_to_start() {
  start.data = 1;
  pub2.publish(&start);
}
void hand_shake() {
  check.data = handshake.c_str();

  // strcpy(check.data, handshake);
  pub1.publish(&check);
}
void ros_setup() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub1);
  nh.advertise(pub);
  nh.advertise(pub1);
  nh.advertise(pub2);
}
void ros_loop() { 
  nh.spinOnce();
}
void pub_to_ros() {

  feedback.data_length = 5;
  feedback.data = mission_array;
  //  feedback.data[5] = tower_step;

  pub.publish(&feedback);
  // delay(100);
}