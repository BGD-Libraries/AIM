#include <LRF.h>
#include <stdint.h>
CLRF LRF(Serial2);

void setup()
{
	Serial.begin(115200);
	Serial2.begin(9600);
	delay(100);
	LRF.init();

}

void loop()
{
	if(LRF.receiveSerialData()) {
		Serial.print(LRF.getDistance());
    Serial.print(" m\n");
	}
}

