/*
* 加载EEPROM中保存的参数
* 尚未开发在线调整参数的功能，EEPROM中为空，会加载默认参数
* 可在此处手动修改PID参数
*/

#include "config.h"
#include <EEPROM.h>
//默认PID参数
#define POSITION_KP  10
#define POSITION_KI  0
#define POSITION_KD  0
#define SPEED_KP     0.5
#define SPEED_KI     0
#define SPEED_KD     0

config_t config;
static saveStruct_t dataTemp;

/***********************************
* 保存PID参数到EEPROM
************************************/
void saveConfig(void)
{
	dataTemp.config_temp = config;
	dataTemp.dataLength = sizeof(dataTemp);
	CRC16_INIT = 0xffff;
	Append_CRC16_Check_Sum((uint8_t *)&dataTemp, dataTemp.dataLength);
	EEPROM.put(0, dataTemp);
	Serial.println("EEPROM save OK");
}


/***********************************
* 从EEPROM中加载PID参数，如果EEPROM未保存PID参数，则加载默认参数
************************************/
void loadConfig(void)
{
	//如果要存到EEPROM的数据大于4k则报错
	while (sizeof(dataTemp) >4000) {
		Serial.println("EEPROM out of range");
	}
	EEPROM.get(0, dataTemp);  //从EEPROM中读取参数
	CRC16_INIT = 0xffff;      //CRC校验初始值
	//CRC校验成功加载PID参数，否则加载默认参数
	if (Verify_CRC16_Check_Sum((uint8_t *)&dataTemp ,sizeof(dataTemp))) {
		config = dataTemp.config_temp;
	} else {
		config.chassis_position_PID.kp = POSITION_KP;
		config.chassis_position_PID.ki = POSITION_KI;
		config.chassis_position_PID.kd = POSITION_KD;
		config.chassis_speed_PID.kp = SPEED_KP;
		config.chassis_speed_PID.ki = SPEED_KI;
		config.chassis_speed_PID.kd = SPEED_KD;
		setLostErrorCode(LOST_ERROR_NOCALI);
	}
}
