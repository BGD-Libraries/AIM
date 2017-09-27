#include "main.h"

int main(void)
{     
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    CAN1_Configuration();                               //CAN1初始化
    
    delay_ms(100);
    CAN_RoboModule_DRV_Reset(0,1);                      //对0组1号驱动器进行复位
    delay_ms(1000);                                     //发送复位指令后的延时必须要有，等待驱动器复位完毕。
    CAN_RoboModule_DRV_Config(0,1,100,0);               //配置为1s传回一次数据
    delay_ms(1);
    CAN_RoboModule_DRV_Mode_Choice(0,1,OpenLoop_Mode);  //选择进入开环模式
    delay_ms(500);                                      //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。

    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0);
    delay_ms(500);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,500);
    delay_ms(500);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,1000);
    delay_ms(10000);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,500);
    delay_ms(500);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0);
    delay_ms(500);
    
    CAN_RoboModule_DRV_Reset(0,1);
    while(1);
}


/*
1.电脑需要提前安装好keil MDK。推荐版本V4.74。
2.本程序适用芯片为STM32F405RGT6，使用8MHz晶振，主频168MHz。
3.如果需要测试CAN的通信，用户所用开发板或者主控板，必须含有CAN收发器，本例程使用的CAN引脚为PA11 PA12。
4.主控芯片如有不同，请自行在工程上修改，CAN引脚如有不同，请自行在can.c文件上修改。
*/
