#include "main.h"

int main(void)
{     
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    CAN1_Configuration();                               //CAN1��ʼ��
    
    delay_ms(100);
    CAN_RoboModule_DRV_Reset(0,1);                      //��0��1�����������и�λ
    delay_ms(1000);                                     //���͸�λָ������ʱ����Ҫ�У��ȴ���������λ��ϡ�
    CAN_RoboModule_DRV_Config(0,1,100,0);               //����Ϊ1s����һ������
    delay_ms(1);
    CAN_RoboModule_DRV_Mode_Choice(0,1,OpenLoop_Mode);  //ѡ����뿪��ģʽ
    delay_ms(500);                                      //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����

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
1.������Ҫ��ǰ��װ��keil MDK���Ƽ��汾V4.74��
2.����������оƬΪSTM32F405RGT6��ʹ��8MHz������Ƶ168MHz��
3.�����Ҫ����CAN��ͨ�ţ��û����ÿ�����������ذ壬���뺬��CAN�շ�����������ʹ�õ�CAN����ΪPA11 PA12��
4.����оƬ���в�ͬ���������ڹ������޸ģ�CAN�������в�ͬ����������can.c�ļ����޸ġ�
*/
