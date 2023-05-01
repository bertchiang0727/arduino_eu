
#include "servocontrol.h"
#include "mainpp.h"

#define servo_ID_1 3
#define servo_ID_2 4
#define servo_ID_3 5
#define servo_ID_4 6
#define vacuum_pin 2
uint16_t servo_angle[4] = { 0 };
int servo_state[4] = { 0 };
int count = 0, temp_pub = 0;
short int mission_array[5] = { 0 };
int vacuum = 0, vacuumservo = 0;
int unload_cherry = 0;
int v_temp = 0;
void setup() {
  // put your setup code here, to run once:
  ros_setup();
  Serial.begin(115200);
  Serial1.begin(500000);
  //init servo
  servo_angle[0] = 1140;
  servo_angle[1] = 1140;
  servo_angle[2] = 1140;
  servo_angle[3] = 1140;
  mission_array[0] = -1;
  UART_Send_SetMotorPosition(servo_ID_1, angle_control_1(1), 300);
  UART_Send_SetMotorPosition(servo_ID_2, angle_control_2(1), 300);
  UART_Send_SetMotorPosition(servo_ID_3, angle_control_3(1), 300);
  UART_Send_SetMotorPosition(servo_ID_4, angle_control_4(1), 300);
  UART_Send_SetMotorPosition(7, vacuum_servo(vacuumservo), 300);
  // analogWrite(vacuum_pin, 180);
     for (int i = 0; i <100; i++) {
        analogWrite(vacuum_pin, i);
        delay(5);
      }
  analogWrite(2, 0);
  delay(300);
  UART_Send_SetMotorPosition(servo_ID_1, angle_control_1(0), 300);
  UART_Send_SetMotorPosition(servo_ID_2, angle_control_2(0), 300);
  UART_Send_SetMotorPosition(servo_ID_3, angle_control_3(0), 300);
  UART_Send_SetMotorPosition(servo_ID_4, angle_control_4(0), 300);
  delay(300);
}
// void loop(){}
void loop() {

  // put your main code here, to run repeatedly:
  if (mission_array[0] == 0 && temp_pub >= 0) {
    UART_Send_SetMotorPosition(servo_ID_1, servo_angle[0], 300);
    UART_Send_SetMotorPosition(servo_ID_2, servo_angle[1], 300);
    UART_Send_SetMotorPosition(servo_ID_3, servo_angle[2], 300);
    UART_Send_SetMotorPosition(servo_ID_4, servo_angle[3], 300);  
    UART_Send_SetMotorPosition(7, vacuum_servo(vacuumservo), 300);  //vacuum
    UART_Send_SetMotorPosition(8, unload_the_cherry(unload_cherry), 300);
    if (vacuum == 1 && v_temp == 0) {
      for (int i = 0; i <180; i++) {
        analogWrite(vacuum_pin, i);
        delay(5);
      }
      // analogWrite(vacuum_pin,255);
      delay(500);
      v_temp = 1;
      mission_array[0] = 1;
    } else if (vacuum == 2 || vacuum == 0) {
      analogWrite(vacuum_pin, 0);
      mission_array[0] = 1;
      v_temp = 0;
    }

    delay(300);
    mission_array[0] = 1;
  }
  if (temp_pub < 1 && mission_array[0] == 1) {
    pub_to_ros();
    temp_pub++;
  }
  // if (v_temp == 1) analogWrite(vacuum_pin, 255);
  ros_loop();
  delay(50);
}
