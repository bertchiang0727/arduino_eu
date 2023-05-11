#include "servocontrol.h"

int Checksum_Calc = 0;

void UART_Send(uint8_t u8_data) {
  // int *u8_pointer = &u8_data;
  Serial1.write(u8_data);
  Checksum_Calc += u8_data;
}

void UART_Send_SetMotorPosition(uint16_t motorId, uint16_t Position,
    uint16_t Time) {
  Checksum_Calc = 0;
  UART_Send(0x80 + motorId);    //header mark & broadcast ID
  UART_Send(0x83);              //header mark & command code
  UART_Send(0x05);              //total data length
  UART_Send((Position / 256) & 0x7F);  //Servo Pos_H
  UART_Send(Position % 256);           //Servo Pos_L
  UART_Send((Time / 256) & 0x7F); //Servo Time_H
  UART_Send(Time % 256);          //Servo Time_L
  UART_Send(Checksum_Calc);     //data length (one servo with time and speed)
}

uint16_t angle_control_1(int state) {
  uint16_t angle = 1140;
  if (state == 0)
    angle = 1140;
  else if (state == 1)
    angle = 1540;
  else if (state == 2)
    angle = 1375;
    
    else if(state==3)
    angle=1440;
  return angle;
}

uint16_t angle_control_2(int state) {
  uint16_t angle = 1140;
  if (state == 0)
    angle = 1140;
  else if (state == 1)
    angle = 1540;
  else if (state == 2)
    angle = 1375;
    else if(state==3)
    angle=1440;
  return angle;
}
uint16_t angle_control_3(int state) {
  uint16_t angle = 1140;
  if (state == 0)
    angle = 1140;
  else if (state == 1)
    angle = 1540;
  else if (state == 2)
    angle = 1375;
    
    else if(state==3)
    angle=1440;
  return angle;
}
uint16_t angle_control_4(int state) {
  uint16_t angle = 1140;
  if (state == 0)
    angle = 1140;
  else if (state == 1)
    angle = 1540;
  else if (state == 2)
    angle = 1375;
    
    else if(state==3)
    angle=1440;
  return angle;
}
int vacuum_servo(int vacuum_servo) {
  uint16_t angle=1950;
  if (vacuum_servo == 0) {
    angle = 1950;
  }
  else if (vacuum_servo == 1) {
    angle = 1700;
  }
  else if (vacuum_servo == 2) {
    angle = 1380;
  }
  else if(vacuum_servo==3){
    angle=1500;
    
  }
  else if(vacuum_servo==4){
      angle=0;
    }
  return angle;
}
int unload_the_cherry(int unload_cherry){
   uint16_t angle=1600;
   if(unload_cherry==1){
     angle=1300;
   }
   else if(unload_cherry==0||unload_cherry==2) {
     angle=1600;
   }
   else if(unload_cherry==3){
     angle=0;
   }
   return angle;
}
