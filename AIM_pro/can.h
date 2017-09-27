#ifndef _CAN_H_
#define _CAN_H_
#include "mcp_can.h"
#include <Arduino.h>

extern MCP_CAN CAN;

void canInit();
void readCANData();

#endif //_CAN_H_