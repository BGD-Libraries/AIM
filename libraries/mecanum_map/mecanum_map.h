#ifndef _MECANUM_H_
#define _MECANUM_H_

#include <Arduino.h>

void mecanum_input_xyw(double speed_x, double speed_y, double speed_w);
void mecanum_output(int16_t *speed1_out, int16_t *speed2_out, int16_t *speed3_out, int16_t *speed4_out);
void mecanum_output(int32_t *speed1_out, int32_t *speed2_out, int32_t *speed3_out, int32_t *speed4_out);
void mecanum_output(double  *speed1_out, double  *speed2_out, double  *speed3_out, double  *speed4_out);

#endif