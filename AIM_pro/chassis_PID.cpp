/****************************************
* 底盘旋转PID
* turnAngle()  设置旋转角度，详见函数定义
* turnoffPID() 关闭PID，关闭后角度设置不再起作用，可手动设置底盘转速
*******************************************/

#include "chassis_PID.h"

#define PID_SAMPLE_TIME 5             //PID计算周期
#define CHASSIS_ROTARY_SPEED_MAX 200  //限定底盘最大转速，单位 度/秒
double initial_angle;                 //底盘初始角度

//位置环PID定义
static double zero = 0;
double chassis_position_input = 0;
double chassis_position_output = 0;
double chassis_position_setpoint = 0;
PID chassis_position_PID(&chassis_position_input, &chassis_position_output, &zero,0,0,0, DIRECT);

//速度环PID定义
double chassis_speed_input = 0;
double chassis_speed_output = 0;
double chassis_speed_setpoint = 0;
PID chassis_speed_PID(&chassis_speed_input, &chassis_speed_output, &chassis_speed_setpoint,0,0,0, DIRECT);

//PID初始化
void chassisPID_init(void)
{
    chassis_position_PID.SetMode(AUTOMATIC);     //启动PID
    chassis_position_PID.SetSampleTime(PID_SAMPLE_TIME);    //设置周期
    chassis_position_PID.SetOutputLimits(-CHASSIS_ROTARY_SPEED_MAX, CHASSIS_ROTARY_SPEED_MAX);//设定范围
    chassis_position_PID.SetTunings(config.chassis_position_PID.kp,
                                    config.chassis_position_PID.ki,
                                    config.chassis_position_PID.kd);
    chassis_position_PID.SetControllerDirection(REVERSE);

    chassis_speed_PID.SetMode(AUTOMATIC);     //启动PID
    chassis_speed_PID.SetSampleTime(PID_SAMPLE_TIME);    //设置周期
    chassis_speed_PID.SetOutputLimits(-CHASSIS_MOTOR_SPEED_MAX / REDUCTION_RATIO *0.4, CHASSIS_MOTOR_SPEED_MAX / REDUCTION_RATIO * 0.4);//设定范围
    chassis_speed_PID.SetTunings(config.chassis_speed_PID.kp,
                                 config.chassis_speed_PID.ki,
                                 config.chassis_speed_PID.kd);
    chassis_speed_PID.SetControllerDirection(DIRECT); //DIRECT,REVERSE

}

/*********************************
* 关闭PID
**********************************/
void turnoffPID(void)
{
    chassis_position_output = 0;
    chassis_position_PID.SetMode(MANUAL);

    chassis_speed_output = 0;
    chassis_speed_PID.SetMode(MANUAL);
}

/******************************************
* 底盘PID处理
******************************************/
void PIDLoop(void)
{
    //因为角度的范围是-180~180，差值运算后需要处理，故放在外部计算差值
    chassis_position_input = angleMap(chassis_position_setpoint - IMU.angle_yaw);
    chassis_position_PID.Compute();     //PID计算

    chassis_speed_input = IMU.gz;
    chassis_speed_setpoint = chassis_position_output;
    chassis_speed_PID.Compute();        //PID计算
    setChassisTurningSpeed(chassis_speed_output);  //设置底盘转速
}

/******************************************
* 获取设定角度与实际角度的差值
******************************************/
double getChassisAngleD(void)
{
    return angleMap(chassis_position_setpoint - IMU.angle_yaw);
}

/******************************
* 获取当前Z轴（YAW轴）角速度
******************************/
double getChassisGz(void)
{
    return IMU.gz;
}


/******************************
* 设定底盘角度
* 角度范围-180~180
* 启动时的角度为0度
* 逆时针转角度增加
* -180和180在位置上相同
* 角度布局如下：
*           0
*       45    -45
*     90        -90
*      135    -135
*        180|-180
*
* 当底盘未转到指定角度时函数返回 0，转到指定角度返回 1
******************************/
int turnAngle(double angle)
{
    if (angle < -180 || angle >180)
        return -1;
    chassis_position_setpoint = angleMap(angle + initial_angle);
    if (abs(getChassisAngleD()) < 5 && abs(getChassisGz()) < 3) //如果角度差小于5度并且角速度小于每秒3度
        return 1;
    else
        return 0;
}