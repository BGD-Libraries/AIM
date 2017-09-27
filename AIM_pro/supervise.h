#ifndef _SUPERVISE_H_
#define _SUPERVISE_H_
#include "_main_.h"
#include <Arduino.h>
#define LOST_ERROR_IMU              (1<<0)      //mpu6050 error
#define LOST_ERROR_MOTOR_LF         (1<<1)
#define LOST_ERROR_MOTOR_LB         (1<<2)
#define LOST_ERROR_MOTOR_RF         (1<<3)
#define LOST_ERROR_MOTOR_RB         (1<<4)
#define LOST_ERROR_LRF_F            (1<<5)
#define LOST_ERROR_LRF_B            (1<<6)
#define LOST_ERROR_DEADLOCK         (1<<7)      //deadlock error
#define LOST_ERROR_NOCALI           (1<<8)      //无PID参数



void supervise(void);
uint32_t getLostErrorCode(void);
uint8_t isLostErrorCodeSet(uint32_t err_code);
void setLostErrorCode(uint32_t err_code);
void resetLostErrorCode(uint32_t err_code);
#endif //_SUPERVISE_H_