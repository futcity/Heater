/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_SONOFF_POW

#define RELAY_PIN_0     12
#define BUTTON_PIN_0    0
#define LED_PIN_0       13
#define DS_SENSOR_PIN   14

OneWire Ow(DS_SENSOR_PIN);
DallasTemperature TempSensor(&Ow);

uint8_t Button = BUTTON_PIN_0;
uint8_t Relay = RELAY_PIN_0;
uint8_t Led = LED_PIN_0;

#endif