#include "IMU.h"

#include "_main_.h"

IMU_struct IMU;

/******************
* IMU初始化
*******************/
void IMUInit(void)
{
	Serial1.begin(115200);
	JY901.attach(Serial1);
}

/****************************
* 接收IMU的数据
****************************/
void updataIMU(void)
{
	if (JY901.receiveSerialData()) {
		//三轴加速度原始值
		IMU.raw_ax = JY901.getAccRawX();
		IMU.raw_ay = JY901.getAccRawY();
		IMU.raw_az = JY901.getAccRawZ();
		//三轴角速度原始值
		IMU.raw_gx = JY901.getGyroRawX();
		IMU.raw_gy = JY901.getGyroRawY();
		IMU.raw_gz = JY901.getGyroRawZ();

		//磁力计易受干扰，未使用
		// IMU.raw_mx = JY901.getMagRaw("x");
		// IMU.raw_my = JY901.getMagRaw("y");
		// IMU.raw_mz = JY901.getMagRaw("z");

		//三轴加速度，单位 g
		IMU.ax = IMU.raw_ax / (32768.0/16.0);
		IMU.ay = IMU.raw_ay / (32768.0/16.0);
		IMU.az = IMU.raw_az / (32768.0/16.0);
		//三轴角速度，单位 度每秒
		IMU.gx = IMU.raw_gx / (32768.0/2000.0);
		IMU.gy = IMU.raw_gy / (32768.0/2000.0);
		IMU.gz = IMU.raw_gz / (32768.0/2000.0);
		// IMU.mx = IMU.raw_mx / (32768.0/180.0);
		// IMU.my = IMU.raw_my / (32768.0/180.0);
		// IMU.mz = IMU.raw_mz / (32768.0/180.0);

		//三轴角度
		IMU.angle_yaw   = JY901.getYaw();
		IMU.angle_pitch = JY901.getPitch();
		IMU.angle_roll  = JY901.getRoll();

		IMU.last_rx_time = JY901.getLastTime();
	}
	if (millis() - IMU.last_rx_time > 50) {
		setLostErrorCode(LOST_ERROR_IMU);
		Serial.println("IMU off line");
	} else {
		resetLostErrorCode(LOST_ERROR_IMU);
	}
}

/****************************
* 将角速度转换到-180至180之内
*****************************/
double angleMap(double angle)
{
  while (angle>180) {
   angle-=360;
  }
  while (angle<-180) {
   angle+=360;
  }
  return angle;
}
