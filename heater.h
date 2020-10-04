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

void HeaterUpdate(bool status);

#endif