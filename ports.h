/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __PORTS_H__
#define __PORTS_H__

#include <WidgetLED.h>

#define VP_STATUS_SWITCH 	V0

#define VP_LED_STATUS	V10
#define VP_LED_HEATER	V11

#define VP_THRESHOLD	V20

#define VP_CUR_TEMP		V30

extern WidgetLED LedStatus;
extern WidgetLED LedHeater;

void PortsInit();

#endif
