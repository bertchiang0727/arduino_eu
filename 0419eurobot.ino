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
int v_temp = 0, k_temp = 0, time = 0, debounce = 0, handshake_temp = 0;
int unplug = 0, plug_before = 3,k=0;

void setup() {
  Serial1.begin(500000);
  ros_setup();

  //init servo
  servo_angle[0] = 1140;
  servo_angle[1] = 1140;
  servo_angle[2] = 1140;
  servo_angle[3] = 1140;

  mission_array[0] = -1;

  UART_Send_SetMotorPosition(servo_ID_1, angle_control_1(1), 0);
  UART_Send_SetMotorPosition(servo_ID_2, angle_control_2(1), 0);
  UART_Send_SetMotorPosition(servo_ID_3, angle_control_3(1), 0);
  UART_Send_SetMotorPosition(servo_ID_4, angle_control_4(1), 0);
  UART_Send_SetMotorPosition(7, vacuum_servo(vacuumservo), 0);
  UART_Send_SetMotorPosition(8, 1400, 0);

  // analogWrite(vacuum_pin, 180);
  for (int i = 0; i < 100; i++) {
    analogWrite(vacuum_pin, i);
    ros_loop();
    delay(5);
  }

  analogWrite(2, 0);
  // delay(300);
  UART_Send_SetMotorPosition(servo_ID_1, angle_control_1(0), 0);
  UART_Send_SetMotorPosition(servo_ID_2, angle_control_2(0), 0);
  UART_Send_SetMotorPosition(servo_ID_3, angle_control_3(0), 0);
  UART_Send_SetMotorPosition(servo_ID_4, angle_control_4(0), 0);
  UART_Send_SetMotorPosition(8, 1600, 0);
}
// void loop(){}
void loop() {
  // UART_Send_SetMotorPosition(servo_ID_1, 1375, 0);
  // UART_Send_SetMotorPosition(servo_ID_2, 1375, 0);
  // UART_Send_SetMotorPosition(servo_ID_3, 1375, 0);
  //  UART_Send_SetMotorPosition(servo_ID_4, 1375, 0);
  //  UART_Send_SetMotorPosition(7, vacuum_servo(3), 0);
  if (plug_before == 0 && digitalRead(3) == 1 && unplug == 0) {
    unplug = 1;
  }
  plug_before = digitalRead(3);

  // put your main code here, to run repeatedly:
  if (mission_array[0] == 0 && temp_pub >= 0) {
    UART_Send_SetMotorPosition(servo_ID_1, servo_angle[0], 0);
    UART_Send_SetMotorPosition(servo_ID_2, servo_angle[1], 0);
    UART_Send_SetMotorPosition(servo_ID_3, servo_angle[2], 0);
    UART_Send_SetMotorPosition(servo_ID_4, servo_angle[3], 0);
    UART_Send_SetMotorPosition(7, vacuum_servo(vacuumservo), 0);  //vacuum

    if (unload_cherry == 1)
      UART_Send_SetMotorPosition(8, unload_the_cherry(unload_cherry), 0);
    if (vacuum == 1 && v_temp == 0) {
      for (int i = 0; i < 180; i++) {
        analogWrite(vacuum_pin, i);
        ros_loop();
        delay(1);
      }
      // analogWrite(vacuum_pin,255);
      // delay(10);
      v_temp = 1;
      mission_array[0] = 1;
    } else if (vacuum == 2 || vacuum == 0) {
      for (int i = 0; i < 20; i++) {
        ros_loop();
        delay(1);
      }
      analogWrite(vacuum_pin, 0);
      mission_array[0] = 1;
      v_temp = 0;
    }
    // delay(10);
    mission_array[0] = 1;
  }
  if (k_temp == 1) {
    UART_Send_SetMotorPosition(servo_ID_1, servo_angle[0], 0);
    UART_Send_SetMotorPosition(servo_ID_2, servo_angle[1], 0);
    UART_Send_SetMotorPosition(servo_ID_3, servo_angle[2], 0);
    UART_Send_SetMotorPosition(servo_ID_4, servo_angle[3], 0);
    k_temp = 0;
  }
  if (temp_pub < 1 && mission_array[0] == 1) {
    pub_to_ros();
    temp_pub++;
  }
  if (handshake_temp++ == 50) {
    hand_shake();
    handshake_temp = 0;
  }
  if (unplug == 1) {
    pub_to_start();
    // Serial.print('i');
    unplug = 2;
  }
  if(k)
  // if (v_temp == 1) analogWrite(vacuum_pin, 255);
  ros_loop();
  delay(1);
  if(unload_cherry==1){
    k++;
  }
  if(k==3000){
    unload_cherry=0;
     UART_Send_SetMotorPosition(8, unload_the_cherry(unload_cherry), 0);
  }
  k++;
}
