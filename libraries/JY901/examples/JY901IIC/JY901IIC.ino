#include <JY901.h>
/*
Test on Uno R3.
JY901    UnoR3
SDA <---> SDA
SCL <---> SCL
*/
void setup() 
{
	Serial.begin(115200);
	JY901.startIIC();
} 

void loop() 
{							 
	Serial.print("Acc:");
	Serial.print(JY901.getAccX());
	Serial.print(" ");
	Serial.print(JY901.getAccY());
	Serial.print(" ");
	Serial.print(JY901.getAccZ());
	Serial.print("\n");

	
	Serial.print("Gyro:");
	Serial.print(JY901.getGyroX());
	Serial.print(" ");
	Serial.print(JY901.getGyroY());
	Serial.print(" ");
	Serial.print(JY901.getGyroZ());
	Serial.print("\n");
	
	Serial.print("Mag:");
	Serial.print(JY901.getMagX());
	Serial.print(" ");
	Serial.print(JY901.getMagY());
	Serial.print(" ");
	Serial.print(JY901.getMagZ());
	Serial.print("\n");

	Serial.print("Angle:");
	Serial.print(JY901.getRoll());
	Serial.print(" ");
	Serial.print(JY901.getPitch());
	Serial.print(" ");
	Serial.print(JY901.getYaw());
	Serial.print("\n");

	Serial.println("");

	delay(500);
}



