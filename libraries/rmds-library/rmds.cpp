#include "rmds.h"
#include "rmds_dfs.h"

Crmds::Crmds(uint32_t temp_machine_ID)
{
    machine_ID = temp_machine_ID;
    autoSendFlag = false;
}

void Crmds::reset()
{
    can_ID = ((machine_ID <<4)|DRV_RESET_ID);
    mode = ENTER_NULL_MODE;
    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::autoSend(bool flag)
{
    autoSendFlag = flag;
}

void Crmds::set_mode(rmds_mode_e temp_mode)
{
    can_ID = ((machine_ID <<4)|DRV_MODE_CHOICE_ID);
    mode = temp_mode;
    if (mode == ENTER_PWM_MODE) {
        pwm      = 0;
        current  = 0;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_PWM_CURRENT_MODE) {
        pwm      = 5000;
        current  = 0;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_PWM_VELOCITY_MODE) {
        pwm      = 5000;
        current  = 0;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_PWM_POSITION_MODE) {
        pwm      = 5000;
        current  = 0;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_PWM_VELOCITY_POSITION_MODE) {
        pwm      = 5000;
        current  = 0;
        velocity = 1000;
        position = 0;
    }
    else if (mode == ENTER_CURRENT_VELOCITY_MODE) {
        pwm      = 0;
        current  = 3000;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_CURRENT_POSITION_MODE) {
        pwm      = 0;
        current  = 3000;
        velocity = 0;
        position = 0;
    }
    else if (mode == ENTER_CURRENT_VELOCITY_POSITION_MODE) {
        pwm      = 0;
        current  = 3000;
        velocity = 1000;
        position = 0;
    }

    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::set_pwm(int16_t temp_pwm)
{
    switch (mode) {
        case ENTER_PWM_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_MODE_ID);
            pwm = constrain(temp_pwm, -5000, 5000);
            break;

        case ENTER_PWM_CURRENT_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_CURRENT_MODE_ID);
            pwm = constrain(temp_pwm, 0, 5000);
            break;

        case ENTER_PWM_VELOCITY_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_VELOCITY_MODE_ID);
            pwm = constrain(temp_pwm, 0, 5000);
            break;

        case ENTER_PWM_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_POSITION_MODE_ID);
            pwm = constrain(temp_pwm, 0, 5000);
            break;

        case ENTER_PWM_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_POSITION_MODE_ID);
            pwm = constrain(temp_pwm, 0, 5000);
            break;

        default:
            break;
    }
    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::set_current(int16_t temp_current)
{
    switch (mode) {
        case ENTER_PWM_CURRENT_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_CURRENT_MODE_ID);
            current = temp_current;
            break;

        case ENTER_CURRENT_VELOCITY_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_MODE_ID);
            current = constrain(temp_current, 0, 32767);
            break;

        case ENTER_CURRENT_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_POSITION_MODE_ID);
            current = constrain(temp_current, 0, 32767);
            break;

        case ENTER_CURRENT_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_POSITION_MODE_ID);
            current = constrain(temp_current, 0, 32767);
            break;

        default:
            break;
    }
    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::set_velocity(int16_t temp_velocity)
{
    switch (mode) {
        case ENTER_PWM_VELOCITY_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_VELOCITY_MODE_ID);
            velocity = temp_velocity;
            break;

        case ENTER_CURRENT_VELOCITY_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_MODE_ID);
            velocity = temp_velocity;
            break;

        case ENTER_PWM_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_VELOCITY_POSITION_MODE_ID);
            velocity = constrain(temp_velocity, 0, 32767);
            break;

        case ENTER_CURRENT_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_POSITION_MODE_ID);
            velocity = constrain(temp_velocity, 0, 32767);
            break;

        default:
            break;
    }
    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::set_position(int32_t temp_position)
{
    switch (mode) {
        case ENTER_PWM_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_POSITION_MODE_ID);
            position = temp_position;
            break;

        case ENTER_PWM_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_PWM_VELOCITY_POSITION_MODE_ID);
            position = temp_position;
            break;

        case ENTER_CURRENT_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_POSITION_MODE_ID);
            position = temp_position;
            break;

        case ENTER_CURRENT_VELOCITY_POSITION_MODE:
            can_ID = ((machine_ID <<4)|DRV_CURRENT_VELOCITY_POSITION_MODE_ID);
            position = temp_position;
            break;

        default:
            break;
    }
    if (autoSendFlag == true)
        Crmds::send_data();
}

void Crmds::config(uint8_t temp_time)
{
    can_ID = ((machine_ID <<4)|DRV_CONFIG_ID);
    return_time = temp_time;
    if (autoSendFlag == true)
        Crmds::send_data();
}

/*描述：将tx_buf中的数据复制到temp_tx_data中
**作用：为了将数据发送出去
*/
void Crmds::write_data(uint32_t *temp_can_ID, uint8_t temp_tx_data[])
{
    *temp_can_ID = can_ID;
    if (can_ID == ((machine_ID <<4)|DRV_RESET_ID) ) {
        temp_tx_data[0] = 0x55;
        temp_tx_data[1] = 0x55;
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_MODE_CHOICE_ID) ) {
        temp_tx_data[0] = mode;
        temp_tx_data[1] = 0x55;
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_PWM_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((pwm>>8)&0xff);
        temp_tx_data[1] = (uint8_t)( pwm    &0xff);
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_PWM_CURRENT_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((pwm>>8)&0xff);
        temp_tx_data[1] = (uint8_t)( pwm    &0xff);
        temp_tx_data[2] = (uint8_t)((current>>8)&0xff);
        temp_tx_data[3] = (uint8_t)((current)   &0xff);
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_PWM_VELOCITY_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((pwm>>8)&0xff);
        temp_tx_data[1] = (uint8_t)( pwm    &0xff);
        temp_tx_data[2] = (uint8_t)((velocity>>8)&0xff);
        temp_tx_data[3] = (uint8_t)( velocity    &0xff);
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_PWM_POSITION_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((pwm>>8)&0xff);
        temp_tx_data[1] = (uint8_t)( pwm    &0xff);
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = (uint8_t)((position>>24)&0xff);
        temp_tx_data[5] = (uint8_t)((position>>16)&0xff);
        temp_tx_data[6] = (uint8_t)((position>>8) &0xff);
        temp_tx_data[7] = (uint8_t)( position     &0xff);
    }
    else if (can_ID == ((machine_ID <<4)|DRV_PWM_VELOCITY_POSITION_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((pwm>>8)&0xff);
        temp_tx_data[1] = (uint8_t)( pwm    &0xff);
        temp_tx_data[2] = (uint8_t)((velocity>>8)&0xff);
        temp_tx_data[3] = (uint8_t)( velocity    &0xff);
        temp_tx_data[4] = (uint8_t)((position>>24)&0xff);
        temp_tx_data[5] = (uint8_t)((position>>16)&0xff);
        temp_tx_data[6] = (uint8_t)((position>>8) &0xff);
        temp_tx_data[7] = (uint8_t)( position     &0xff);
    }
    else if (can_ID == ((machine_ID <<4)|DRV_CURRENT_VELOCITY_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((current>>8)&0xff);
        temp_tx_data[1] = (uint8_t)((current)   &0xff);
        temp_tx_data[2] = (uint8_t)((velocity>>8)&0xff);
        temp_tx_data[3] = (uint8_t)( velocity    &0xff);
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
    else if (can_ID == ((machine_ID <<4)|DRV_CURRENT_POSITION_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((current>>8)&0xff);
        temp_tx_data[1] = (uint8_t)((current)   &0xff);
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = (uint8_t)((position>>24)&0xff);
        temp_tx_data[5] = (uint8_t)((position>>16)&0xff);
        temp_tx_data[6] = (uint8_t)((position>>8) &0xff);
        temp_tx_data[7] = (uint8_t)( position     &0xff);
    }
    else if (can_ID == ((machine_ID <<4)|DRV_CURRENT_VELOCITY_POSITION_MODE_ID) ) {
        temp_tx_data[0] = (uint8_t)((current>>8)&0xff);
        temp_tx_data[1] = (uint8_t)((current)   &0xff);
        temp_tx_data[2] = (uint8_t)((velocity>>8)&0xff);
        temp_tx_data[3] = (uint8_t)( velocity    &0xff);
        temp_tx_data[4] = (uint8_t)((position>>24)&0xff);
        temp_tx_data[5] = (uint8_t)((position>>16)&0xff);
        temp_tx_data[6] = (uint8_t)((position>>8) &0xff);
        temp_tx_data[7] = (uint8_t)( position     &0xff);
    }
    else if (can_ID == ((machine_ID <<4)|DRV_CONFIG_ID) ) {
        temp_tx_data[0] = return_time;
        temp_tx_data[1] = 0x55;
        temp_tx_data[2] = 0x55;
        temp_tx_data[3] = 0x55;
        temp_tx_data[4] = 0x55;
        temp_tx_data[5] = 0x55;
        temp_tx_data[6] = 0x55;
        temp_tx_data[7] = 0x55;
    }
}

bool Crmds::read_data(uint32_t *temp_can_ID, uint8_t temp_rx_data[])
{
    if (*temp_can_ID == ((machine_ID <<4)|DRV_RETURN_ID) ) {
        last_rx_time = millis();
        real_current =  (((uint16_t)temp_rx_data[0]<<8)|(uint16_t)temp_rx_data[1]);
        real_velocity = (((uint16_t)temp_rx_data[2]<<8)|(uint16_t)temp_rx_data[3]);
        real_position = (((uint32_t)temp_rx_data[4]<<24)|((uint32_t)temp_rx_data[5]<<16)|((uint32_t)temp_rx_data[6]<<8)|(uint32_t)temp_rx_data[7]);
        return true;
    }
    return false;
}

void Crmds::send_data(void)
{
    static uint32_t can_ID;
    static uint8_t tx_data[8];
    Crmds::write_data(&can_ID, tx_data);
    send(&can_ID, tx_data);
}

void Crmds::register_callback(void (*callBackfun)(uint32_t *, uint8_t *))
{
    if (callBackfun == NULL)
        return;
    send = callBackfun;
}

int16_t Crmds::get_real_current()
{
    return real_current;
}

int16_t Crmds::get_real_velocity()
{
    return real_velocity;
}

int32_t Crmds::get_real_position()
{
    return real_position;
}

unsigned long Crmds::get_rx_time()
{
    return last_rx_time;
}
