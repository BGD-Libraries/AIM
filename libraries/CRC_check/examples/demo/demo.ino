#include "crc_check.h"
#include <stdint.h>

uint8_t rxBuffer[128];
uint8_t rxCnt = 0;
uint16_t dataLength = 0;
void setup()
{
	Serial.begin(115200);
	Serial2.begin(115200);
}

void loop()
{
	while (Serial2.available()) {
		rxBuffer[rxCnt] = Serial2.read();
		rxCnt++;
		if (rxBuffer[0] != 0xA5) {
			rxCnt = 0;
		}
		if (rxCnt == 4) {
			if (Verify_CRC8_Check_Sum(rxBuffer,4) == 0) {
				rxCnt = 0;
			}
			else{
				dataLength = ((uint16_t)rxBuffer[1]|(uint16_t)rxBuffer[2]<<8);
			}

		}
		if (rxCnt == dataLength + 8) {
			if ( Verify_CRC16_Check_Sum(rxBuffer,dataLength + 8) ) {
				Serial.println(1);
			}
			else
				rxCnt = 0;
		}
		if (rxCnt >=127) {
			rxCnt = 0;
		}
	}
}
