#include <JY901.h>

void setup() 
{
	Serial.begin(115200);
  Serial1.begin(115200);
	JY901.attach(Serial1);
}

void loop() 
{
	if (JY901.receiveSerialData()) {				 
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
	}


}


