#ifndef _CHASSIS_PID_H_
#define _CHASSIS_PID_H_

#include "PID_v1.h"
#include <Arduino.h>
#include "_main_.h"

extern double initial_angle;

extern double chassis_position_input;
extern double chassis_position_output;
extern double chassis_position_setpoint;
extern PID chassis_position_PID;

extern double chassis_speed_input;
extern double chassis_speed_output;
extern double chassis_speed_setpoint;
extern PID chassis_speed_PID;

void chassisPID_init(void);
void turnoffPID(void);
void PIDLoop(void);
double getChassisAngleD(void);
double getChassisGz(void);
int turnAngle(double angle);

#endif //_CHASSIS_PID_H_
