#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include <Arduino.h>
#include "_main_.h"
#include "rmds.h"


#define CHASSIS_MOTOR_SPEED_MAX  13000     //电动机经减速器前最大转速，单位RPM
#define REDUCTION_RATIO 64                 //电动机减速比

extern Crmds motor_LF;
extern Crmds motor_LB;
extern Crmds motor_RF;
extern Crmds motor_RB;

void chassisInit(void);
void chassisLoop(void);
void setChassisForwardSpeed(double speed_y_);
void setChassisTurningSpeed(double speed_w_);
void turnOffMotor(void);
void turnOnMotor(void);

#endif //_MOTOR_CONTROL_H_