#include "_main_.h"

void setup()
{
	Serial.begin(115200);
	IMUInit();          //IMU初始化
	canInit();          //CAN初始化
	loadConfig();       //加载PID参数
	chassisInit();      //电机驱动板初始化
	sensorInit();       //激光测距仪初始化
	//获取YAW轴初始角度
	unsigned long start_time = millis();
	while (1) {
		updataIMU();
		if ((IMU.last_rx_time >= 500 + start_time)){
			initial_angle = IMU.angle_yaw;  //获得初始角度
			chassis_position_setpoint = initial_angle;   //把初始角度作为当前角度设定值
			chassisPID_init();    //pid初始化
			break;
		}
	}
	Serial.println("begin!");
}

void loop()
{

	(**task_function)();  //任务

	sensorLoop();     //激光测距
	readCANData();       //读取can数据
	updataIMU();         //更新IMU的数据
	PIDLoop();        //PID计算循环
	chassisLoop();    //电机控制处理,每2ms执行一次
	supervise();         //运行状态监控
}

