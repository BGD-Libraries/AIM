#include <mecanum_map.h>


double x=100, y=100 , w=0;
int16_t speed1, speed2, speed3, speed4;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	mecanum_input_xyw(x,y,w);
	mecanum_output(&speed1, &speed2, &speed3, &speed4);
	Serial.print(speed1);
	Serial.print("\t");
	Serial.print(speed2);
	Serial.print("\t");
	Serial.print(speed3);
	Serial.print("\t");
	Serial.print(speed4);
	Serial.print("\n");
	delay(300);
}