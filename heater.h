/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __HEATER_H__
#define __HEATER_H__

#include <Arduino.h>

#define TEMP_ERR_VAL	-127
#define DEFAULT_SENSOR	0
#define TEMP_RETRIES	5

uint8_t HeaterGetThreshold();
void HeaterSetThreshold(uint8_t val);
bool HeaterGetStatus();
void HeaterSetStatus(bool val);
void HeaterSwitchStatus();
void HeaterUpdate();

#endif