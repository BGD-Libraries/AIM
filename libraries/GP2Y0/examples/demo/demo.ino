#include <GP2Y0.h>

void setup()
{
	pinMode(A0, INPUT);
	Serial.begin(9600);
}

void loop()
{
	Serial.println(GP2Y0A02(A0));
	delay(300);
}