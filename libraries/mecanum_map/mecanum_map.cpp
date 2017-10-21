/****************************************************
** x代表横移速度，向右为正
** y代表前进速度，向前为正
** w代表转弯速度，逆时针为正
** speed1~speed4是四个轮子的速度，按数学坐标象限排列
*****************************************************/

#include "mecanum_map.h"

static double speed1, speed2, speed3, speed4;

void mecanum_input_xyw(double speed_x, double speed_y, double speed_w)
{
	double max_val = max( max(abs(speed_y), abs(speed_x)), abs(speed_w));
	double sum = abs(speed_y) + abs(speed_x) + abs(speed_w);
	if(sum==0)
		sum=1;
	double speed_map_x = speed_x * (max_val / sum);  //横移速度
	double speed_map_y = speed_y * (max_val / sum);  //前进速度
	double speed_map_w = speed_w * (max_val / sum);  //转弯速度
	speed1 = speed_map_y - speed_map_x + speed_map_w;
	speed2 = speed_map_y + speed_map_x - speed_map_w;
	speed3 = speed_map_y - speed_map_x - speed_map_w;
	speed4 = speed_map_y + speed_map_x + speed_map_w;
}

void mecanum_output(int16_t *speed1_out, int16_t *speed2_out, int16_t *speed3_out, int16_t *speed4_out)
{
	*speed1_out = constrain(speed1, -32767, 32767);
	*speed2_out = constrain(speed2, -32767, 32767);
	*speed3_out = constrain(speed3, -32767, 32767);
	*speed4_out = constrain(speed4, -32767, 32767);
}

void mecanum_output(int32_t *speed1_out, int32_t *speed2_out, int32_t *speed3_out, int32_t *speed4_out)
{
	*speed1_out = constrain(speed1, -2147483647, 2147483647);
	*speed2_out = constrain(speed2, -2147483647, 2147483647);
	*speed3_out = constrain(speed3, -2147483647, 2147483647);
	*speed4_out = constrain(speed4, -2147483647, 2147483647);
}

void mecanum_output(double *speed1_out, double *speed2_out, double *speed3_out, double *speed4_out)
{
	*speed1_out = speed1;
	*speed2_out = speed2;
	*speed3_out = speed3;
	*speed4_out = speed4;
}