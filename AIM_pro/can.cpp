/******************************
* can总线处理
******************************/

#include "can.h"
#include "_main_.h"
#define SPI_CS_PIN 40

uint8_t CAN_len = 0;        //数据长度
uint8_t can_rx_data[8];     //接收的数据
uint32_t CAN_ID;            //数据ID

MCP_CAN CAN(SPI_CS_PIN);    //SPI转can模块


/*SPI转can模块初始化，设置波特率为 1M Hz*/
void canInit()
{
	while(1){
		if (CAN_OK == CAN.begin(CAN_1000KBPS)) {
			Serial.println("CAN BUS Shield init ok!");
			break;
		} else {
			Serial.println("CAN BUS Shield init fail");
			delay(100);
		}
	}
}

/*接收can数据*/
void readCANData()
{
	if (CAN_MSGAVAIL == CAN.checkReceive()) {
		CAN.readMsgBufID(&CAN_ID,&CAN_len,can_rx_data);   //接收can数据
		motor_LF.read_data(&CAN_ID,can_rx_data);
		motor_LB.read_data(&CAN_ID,can_rx_data);
		motor_RF.read_data(&CAN_ID,can_rx_data);
		motor_RB.read_data(&CAN_ID,can_rx_data);
	}
}