#include "rmds.h"
#include <mcp_can.h>


/*CAN 配置*/
const int SPI_CS_pin = 40;
MCP_CAN CAN(SPI_CS_pin);
uint8_t CAN_len = 0;        //数据长度
uint8_t can_tx_data[8];
uint8_t can_rx_data[8];
uint32_t CAN_ID=0;

Crmds motor1(0x01);
unsigned long timePoint;
int32_t x;
void setup()
{
	Serial.begin(115200);
	/*CAN 初始化*/
	while(1){
		if(CAN_OK == CAN.begin(CAN_1000KBPS)){
			Serial.println("CAN BUS Shield init ok!");
			break;
		}
		else{
			Serial.println("CAN BUS Shield init fail");
			Serial.println("Init CAN BUS Shield again");
			delay(100);
		}
	}

	/*电机驱动板初始化*/
	motor1.reset();
	motor1.write_data(&CAN_ID, can_tx_data);
	CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	delay(500);  //复位后需要等待500ms
	/*配置反馈*/
	motor1.config(1);
	motor1.write_data(&CAN_ID, can_tx_data);
	CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	delay(500);
	/*选择PWM-速度-位置模式*/
	//motor1.set_mode(ENTER_CURRENT_POSITION_MODE);
	motor1.set_mode(ENTER_PWM_VELOCITY_POSITION_MODE);
	motor1.write_data(&CAN_ID, can_tx_data);
	CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
	delay(500);  //设置模式后需要等待500ms
}

void loop()
{
	if(CAN_MSGAVAIL == CAN.checkReceive()) {            // check if data coming
        CAN.readMsgBufID(&CAN_ID,&CAN_len,can_rx_data);   //接收can数据
        motor1.read_data(&CAN_ID,can_rx_data);
        Serial.println(motor1.get_real_position());
    }

    if (millis() - timePoint>=3000) {
    	if (x == 0)
    		x = 128000;
    	else
    		x = 0;
    	timePoint = millis();
    	motor1.set_position(x);
		motor1.write_data(&CAN_ID, can_tx_data);
		CAN.sendMsgBuf(CAN_ID, 0, 8, can_tx_data);
    }
}