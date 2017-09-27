#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <Arduino.h>
#include "LRF.h"

void sensorInit();
void sensorLoop();
double getFrontDistance(void);
double getBackDistance(void);
#endif  //_SENSOR_H_