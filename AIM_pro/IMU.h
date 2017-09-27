#ifndef _IMU_H_
#define _IMU_H_
#include <Arduino.h>

#include "JY901.h"

//IMU参数结构体
typedef struct
{
	double angle_yaw;
	double angle_pitch;
	double angle_roll;
	int16_t raw_ax;
	int16_t raw_ay;
	int16_t raw_az;
	int16_t raw_gx;
	int16_t raw_gy;
	int16_t raw_gz;
	int16_t raw_mx;
	int16_t raw_my;
	int16_t raw_mz;
	double ax;
	double ay;
	double az;
	double gx;
	double gy;
	double gz;
	double mx;
	double my;
	double mz;
	unsigned long last_rx_time;
}IMU_struct;

extern IMU_struct IMU;

void IMUInit(void);
void updataIMU(void);
double angleMap(double angle);
#endif //_IMU_H_