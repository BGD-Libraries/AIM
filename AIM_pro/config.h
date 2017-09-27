/*配置信息和保存及加载flash的操作*/
#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <Arduino.h>
#include "crc_check.h"
#include "_main_.h"

//PID结构体
typedef struct
{
	double kp;
	double ki;
	double kd;
}PIDParameterStruct_t;

//配置参数结构体
typedef struct
{
	PIDParameterStruct_t chassis_position_PID;
	PIDParameterStruct_t chassis_speed_PID;
}config_t;

//保存参数结构体
typedef struct
{
	int16_t dataLength;
	config_t config_temp;
	uint8_t crc16[2];
}saveStruct_t;


extern config_t config;
extern uint8_t PID_input_type_flag;
void saveConfig(void);    //保存配置到EEPROM
void loadConfig(void);    //从EEPROM读取数据


#endif
