/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#ifndef __BOARDS_H__
#define __BOARDS_H__

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define BOARD_SONOFF_POW

extern uint8_t Button;
extern uint8_t Relay;
extern uint8_t Led;
extern DallasTemperature TempSensor;

#endif