#include "LRF.h"

CLRF::CLRF(Stream &Serial_temp)
{
	_Serial = &Serial_temp;
}

void CLRF::init()
{
	uint8_t cmd[4]={0x80,0x06,0x03,0x77};  //连续测量
	_Serial->write(cmd,4);
}

bool CLRF::receiveSerialData()
{
	bool state = false;
	if (_Serial->available()) {
		do {
			if (_Serial->peek() != 0x80) {  //第一个字节是否为0x80,如果不是丢弃
				_Serial->read();
			} else {
				if (_Serial->available() >= 11) {  //可接收数据是否达到要求
					_Serial->readBytes(rxBuffer, 11); //读取数据
					if (CLRF::getCheckSum(rxBuffer,11) == rxBuffer[10]) {
						if (0x30<=rxBuffer[3] &&rxBuffer[3]<=0x39)
						if (0x30<=rxBuffer[4] &&rxBuffer[4]<=0x39)
						if (0x30<=rxBuffer[5] &&rxBuffer[5]<=0x39)
						if (rxBuffer[6] == 0x2E)
						if (0x30<=rxBuffer[7] &&rxBuffer[7]<=0x39)
						if (0x30<=rxBuffer[8] &&rxBuffer[8]<=0x39)
						if (0x30<=rxBuffer[9] &&rxBuffer[9]<=0x39) 
						{
							distance = (double)(rxBuffer[3]-0x30)*100.0  +
									   (double)(rxBuffer[4]-0x30)*10.0   +
									   (double)(rxBuffer[5]-0x30)*1.0    +
									   (double)(rxBuffer[7]-0x30)/10.0   +
									   (double)(rxBuffer[8]-0x30)/100.0  +
									   (double)(rxBuffer[9]-0x30)/1000.0; 
							state = true;
							lastTime = millis();
						}
					}
				}
			}
		}while(_Serial->available() >= 11);
	}
	return state;
}


uint8_t CLRF::getCheckSum(uint8_t buf[],uint8_t length)
{
	uint8_t temp = 0;
	for (int cnt=0;cnt < length - 1;cnt++) {
		temp += buf[cnt];
	}

	return (~temp)+1;
}

double CLRF::getDistance(void)
{
	return distance;
}

unsigned long CLRF::getLastTime()
{
	return lastTime;
}
