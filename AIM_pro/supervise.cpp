/********************************************
* 设备运行状态自检、监控
*********************************************/

#include "supervise.h"

static uint32_t robot_error_code;
static unsigned long loop_time = 0;

void supervise(void)
{
	static unsigned long timepoint = millis();
	if (millis() - timepoint >=100) {
		timepoint = millis();
		if (Serial) {
			Serial.print("loop time(us): ");   //输出运行周期，小于5ms为正常周期
			Serial.print(micros() - loop_time);
			Serial.print("\t");
			Serial.print("error code: ");      //输出设备错误码
			Serial.println(getLostErrorCode(),BIN);
		}
	}
	//如果IMU掉线，则关闭电机，防止失控
	if (isLostErrorCodeSet(LOST_ERROR_IMU)) {
		turnOffMotor();
	} else {
		turnOnMotor();
	}
	loop_time = micros();
}



uint32_t getLostErrorCode(void)
{
	return robot_error_code;
}
uint8_t isLostErrorCodeSet(uint32_t err_code)
{
	if (err_code & robot_error_code) {
		return 1;
	} else {
		return 0;
	}
}
void setLostErrorCode(uint32_t err_code)
{
	robot_error_code |= err_code;
}
void resetLostErrorCode(uint32_t err_code)
{
	robot_error_code &= ~err_code;
}
