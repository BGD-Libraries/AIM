#include <Servo.h>
#include "rmds.h"
#include "mcp_can.h"
#include "LRF.h"
#define SPI_CS_PIN 40
#define SPEED 2000
Crmds motor_LF(0x01);
Crmds motor_LB(0x02);
Crmds motor_RF(0x03);
Crmds motor_RB(0x04);
MCP_CAN CAN(SPI_CS_PIN);

Servo Servo_A; //腰部（A） 
Servo Servo_B; //大臂（B）
Servo Servo_C; //小臂（C）
Servo Servo_D; //腕部（D）

CLRF LRF_F(Serial2);
CLRF LRF_B(Serial3);

void can_send_call_back(uint32_t *can_ID, uint8_t *can_tx_data)
{
  CAN.sendMsgBuf(*can_ID, 0, 8, can_tx_data);
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  LRF_F.init();
  LRF_B.init();
  /*初始化舵机*/
  Servo_A.attach(20);  
  Servo_B.attach(21); 
  Servo_C.attach(22); 
  Servo_D.attach(23);
  while(1){
    if (CAN_OK == CAN.begin(CAN_1000KBPS)) {
      Serial.println("CAN BUS Shield init ok!");
      break;
    } else {
      Serial.println("CAN BUS Shield init fail");
      delay(100);
    }
  }
  motorInit();
}

void loop() {
  forward();
  delay(5000);
  stop();
  delay(500);
  left();
  delay(2000);  
  stop();
  delay(500);
}

void motorInit()
{
  //注册回调函数
  motor_LF.register_callback(can_send_call_back);
  motor_LF.autoSend(true);
  motor_LB.register_callback(can_send_call_back);
  motor_LB.autoSend(true);
  motor_RF.register_callback(can_send_call_back);
  motor_RF.autoSend(true);
  motor_RB.register_callback(can_send_call_back);
  motor_RB.autoSend(true);
  /*复位*/
  motor_LF.reset();
  motor_LB.reset();
  motor_RF.reset();
  motor_RB.reset();
  delay(500);  //复位后需要等待500ms
  /*设置模式为PWM速度模式*/
  motor_LF.set_mode(ENTER_PWM_VELOCITY_MODE);
  motor_LB.set_mode(ENTER_PWM_VELOCITY_MODE);
  motor_RF.set_mode(ENTER_PWM_VELOCITY_MODE);
  motor_RB.set_mode(ENTER_PWM_VELOCITY_MODE);
  delay(500);  //设置模式后需要等待500ms
}

void forward()
{
  motor_LF.set_velocity(-SPEED);
  motor_LB.set_velocity(-SPEED);
  motor_RF.set_velocity(SPEED);
  motor_RB.set_velocity(SPEED);
}

void back()
{
  motor_LF.set_velocity(SPEED);
  motor_LB.set_velocity(SPEED);
  motor_RF.set_velocity(-SPEED);
  motor_RB.set_velocity(-SPEED);
}

void left()
{
  motor_LF.set_velocity(SPEED);
  motor_LB.set_velocity(SPEED);
  motor_RF.set_velocity(SPEED);
  motor_RB.set_velocity(SPEED);
}

void right()
{
  motor_LF.set_velocity(-SPEED);
  motor_LB.set_velocity(-SPEED);
  motor_RF.set_velocity(-SPEED);
  motor_RB.set_velocity(-SPEED);
}

void stop()
{
  motor_LF.set_velocity(0);
  motor_LB.set_velocity(0);
  motor_RF.set_velocity(0);
  motor_RB.set_velocity(0);
}

