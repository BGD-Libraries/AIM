/************************************
* 路径规划
************************************/

#include "task.h"

static unsigned long time_point = 0;
static unsigned long time_count = 0;
static void (**task_begin)();

static void forward1(void)
{
	if (getFrontDistance() < 0.3) {
		setChassisForwardSpeed(0);
	} else {
		setChassisForwardSpeed(80);
		if (millis() - time_point >= 1) {
			time_count++;
			time_point = millis();
		}
	}
	if (time_count >= 800) {
		*task_function++;
		setChassisForwardSpeed(0);
		time_count = 0;
	}

}


static void turn90(void)
{
	if (turnAngle(90)) {
		*task_function++;
	}
}

static void turn180(void)
{
	if (turnAngle(180)) {
		*task_function++;
	}
}

static void turnN90(void)
{
	if (turnAngle(-90)) {
		*task_function++;
	}
}

static void turn0(void)
{
	if (turnAngle(0)) {
		*task_function++;
	}
}

static void wait(void)
{
	static int state = 0;
	if (state == 0) {
		time_point = millis();
		state = 1;
	}
	if (millis() - time_point >= 1000) {
		task_function++;
		state = 0;
		time_point = millis();
	}
}

static void restart()
{
	task_function = task_begin;
}

static void finish(void)
{
	return;
}

static void (*task_list[])() =
{
	forward1,
	wait,
	turn90,
	wait,

	forward1,
	wait,
	turn180,
	wait,

	forward1,
	wait,
	turnN90,
	wait,

	forward1,
	wait,
	turn0,
	wait,

	restart,
	finish,
};

void (**task_function)(void) = task_begin = task_list;

