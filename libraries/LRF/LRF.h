#ifndef _LRF_H_
#define _LRF_H_

#include <arduino.h>

class CLRF
{
 public:
	CLRF(Stream &Serial_temp);
	void init();
	bool receiveSerialData();
	double getDistance(void);
	unsigned long getLastTime();
 private:
 	Stream *_Serial;
 	uint8_t getCheckSum(uint8_t buf[],uint8_t length);
 	uint8_t rxCnt;
 	uint8_t rxBuffer[16];
 	double distance;
 	unsigned long lastTime;
};

#endif
