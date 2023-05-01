#pragma once

#ifdef __cplusplus

extern "C" {

#endif


void UART_Send(uint8_t u8_data);

void UART_Send_SetMotorPosition(uint16_t motorId, uint16_t Position,
    uint16_t Time);
uint16_t angle_control_1(int state);
uint16_t angle_control_2(int state);
uint16_t angle_control_3(int state);
uint16_t angle_control_4(int state);
int vacuum_servo(int vacuum_servo);
int unload_the_cherry(int unload_cherry);

#ifdef __cplusplus
}

#endif
