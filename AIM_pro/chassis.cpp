/*********************************
* 底盘电机操作
* setChassisForwardSpeed() 设置前进后退速度
* setChassisTurningSpeed() 设置转弯速度，由底盘PID自动设置，如果想手动设置需要先关闭PID
**********************************/

#include "chassis.h"
#include "mecanum_map.h"

static bool motor_is_on = true;
static double speed_y = 0, speed_x = 0, speed_w = 0;

Crmds motor_LF(0x01);
Crmds motor_LB(0x02);
Crmds motor_RF(0x03);
Crmds motor_RB(0x04);

/******************************************
* can数据发送回调函数
*******************************************/
static void can_send_call_back(uint32_t *can_ID, uint8_t *can_tx_data)
{
    CAN.sendMsgBuf(*can_ID, 0, 8, can_tx_data);
}


/******************************************
* 底盘电机驱动板初始化
*******************************************/
void chassisInit(void)
{
	//注册回调函数
    motor_LF.register_callback(can_send_call_back);
    motor_LF.autoSend(true);
    motor_LB.register_callback(can_send_call_back);
    motor_LB.autoSend(true);
    motor_RF.register_callback(can_send_call_back);
    motor_RF.autoSend(true);
    motor_RB.register_callback(can_send_call_back);
    motor_RB.autoSend(true);

	/*复位*/
	motor_LF.reset();
	motor_LB.reset();
	motor_RF.reset();
	motor_RB.reset();
	delay(500);  //复位后需要等待500ms

	//驱动板数据反馈时间并不稳定，
	//因此取消这个功能，不影响使用
	// /*配置数据反馈时间ms*/
	// motor_LF.config(10);
	// motor_LF.write_data(&CAN_ID, can_tx_data);
	// CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	// motor_LB.config(10);
	// motor_LB.write_data(&CAN_ID, can_tx_data);
	// CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	// motor_RF.config(10);
	// motor_RF.write_data(&CAN_ID, can_tx_data);
	// CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	// motor_RB.config(10);
	// motor_RB.write_data(&CAN_ID, can_tx_data);
	// CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	// delay(500);

	/*设置模式为PWM-速度模式*/
	motor_LF.set_mode(ENTER_PWM_VELOCITY_MODE);
	motor_LB.set_mode(ENTER_PWM_VELOCITY_MODE);
	motor_RF.set_mode(ENTER_PWM_VELOCITY_MODE);
	motor_RB.set_mode(ENTER_PWM_VELOCITY_MODE);
	delay(500);  //设置模式后需要等待500ms
}

/*********************************************
* 设置底盘前进后退的速度，可在task中调用此函数
*********************************************/
void setChassisForwardSpeed(double speed_y_)
{
	speed_y = constrain(speed_y_ * REDUCTION_RATIO, -CHASSIS_MOTOR_SPEED_MAX, CHASSIS_MOTOR_SPEED_MAX);
}

/*********************************************
* 设置底盘转弯的速度，由PID程序自动设置
*********************************************/
void setChassisTurningSpeed(double speed_w_)
{
	speed_w = constrain(speed_w_ * REDUCTION_RATIO, -CHASSIS_MOTOR_SPEED_MAX, CHASSIS_MOTOR_SPEED_MAX);
}

/*********************************************
* 底盘驱动处理函数
*********************************************/
void chassisLoop(void)
{
	static unsigned long timepoint = millis();
	if (millis() - timepoint >=2) {  //驱动板最短数据发送周期为2ms
		timepoint = millis();

		int16_t LF_motor_set_speed;
		int16_t LB_motor_set_speed;
		int16_t RF_motor_set_speed;
		int16_t RB_motor_set_speed;

		//速度归一化处理
		mecanum_xyw_input(speed_x, speed_y, speed_w);
		mecanum_map_output(&RF_motor_set_speed, &LF_motor_set_speed, &LB_motor_set_speed, &RB_motor_set_speed);

		//向电机驱动器发送数据
		if (motor_is_on) {
			motor_LF.set_velocity(-LF_motor_set_speed);
			motor_LB.set_velocity(-LB_motor_set_speed);
			motor_RF.set_velocity(RF_motor_set_speed);
			motor_RB.set_velocity(RB_motor_set_speed);
		} else {
			if (!isLostErrorCodeSet(LOST_ERROR_MOTOR_LF)) {
				motor_LF.set_velocity(0);
			}
			if (!isLostErrorCodeSet(LOST_ERROR_MOTOR_LB)) {
				motor_LB.set_velocity(0);
			}
			if (!isLostErrorCodeSet(LOST_ERROR_MOTOR_RF)) {
				motor_RF.set_velocity(0);
			}
			if (!isLostErrorCodeSet(LOST_ERROR_MOTOR_RB)) {
				motor_RB.set_velocity(0);
			}
		}
		//驱动板数据反馈时间并不稳定，
		//因此取消这个功能，不影响使用
		// /*左前电机*/
		// if (millis()-motor_LF.get_rx_time() >=5000) {
		// 	setLostErrorCode(LOST_ERROR_MOTOR_LF);
		// 	Serial.println("左前电机掉线");
		// } else {
		// 	resetLostErrorCode(LOST_ERROR_MOTOR_LF);
		// }
		// /*左后电机*/
		// if (millis()-motor_LB.get_rx_time() >=5000) {
		// 	setLostErrorCode(LOST_ERROR_MOTOR_LB);
		// 	Serial.println("左后电机掉线");
		// } else {
		// 	resetLostErrorCode(LOST_ERROR_MOTOR_LB);
		// }
		// /*右前电机*/
		// if (millis()-motor_RF.get_rx_time() >=5000) {
		// 	setLostErrorCode(LOST_ERROR_MOTOR_RF);
		// 	Serial.println("右前电机掉线");
		// } else {
		// 	resetLostErrorCode(LOST_ERROR_MOTOR_RF);
		// }
		// /*右后电机*/
		// if (millis()-motor_LB.get_rx_time() >=5000) {
		// 	setLostErrorCode(LOST_ERROR_MOTOR_RB);
		// 	Serial.println("右后电机掉线");
		// } else {
		// 	resetLostErrorCode(LOST_ERROR_MOTOR_RB);
		// }
	}
}

/*********************************************
* 底盘电机默认为开，当出现严重错误时，例如IMU模块异常
* 程序中会调用turnOffMotor()将电机关闭
**********************************************
* 底盘电机关
*********************************************/
void turnOffMotor(void)
{
	motor_is_on= false;
}

/*********************************************
* 底盘电机开
*********************************************/
void turnOnMotor(void)
{
	motor_is_on = true;
}