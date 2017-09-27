#include "sensor.h"
#include "_main_.h"

CLRF FLRF(Serial2);
CLRF BLRF(Serial3);

static double front_distance;
static double back_distance;
static unsigned long front_sensor_time;
static unsigned long back_sensor_time;

double getFrontDistance(void)
{
	return front_distance;
}

double getBackDistance(void)
{
	return back_distance;
}

void sensorInit()
{
	Serial2.begin(9600);
	Serial3.begin(9600);
	delay(100);
	FLRF.init();
	BLRF.init();
}

void sensorLoop()
{
	if (FLRF.receiveSerialData()) {
		front_sensor_time = millis();
		front_distance = FLRF.getDistance();
	}

	if (BLRF.receiveSerialData()) {
		back_sensor_time = millis();
		back_distance = BLRF.getDistance();
	}

	if (millis() -front_sensor_time >= 5000) { //前激光测距
		setLostErrorCode(LOST_ERROR_LRF_F);
		Serial.println("FLRF off line");
	} else {
		resetLostErrorCode(LOST_ERROR_LRF_F);
	}
	if (millis() - back_sensor_time >= 5000) { //后激光测距
		setLostErrorCode(LOST_ERROR_LRF_B);
		Serial.println("BLRF off line");
	} else {
		resetLostErrorCode(LOST_ERROR_LRF_B);
	}
}

