/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "boards.h"

#ifdef BOARD_SONOFF_POW

#define HEATER_PIN      12

#define BUTTON_MAIN_PIN 0
#define LED_STATUS_PIN  13

#define DS_SENSOR_PIN   14

OneWire Ow(DS_SENSOR_PIN);
DallasTemperature AirTemp(&Ow);

uint8_t Buttons[] = {
    BUTTON_MAIN_PIN
};

uint8_t ButtonsCount = ARRAY_ITEMS_COUNT(Buttons);

uint8_t Relays[] = {
    HEATER_PIN
};

uint8_t RelaysCount = ARRAY_ITEMS_COUNT(Relays);

uint8_t Leds[] = {
    LED_STATUS_PIN
};

uint8_t LedsCount = ARRAY_ITEMS_COUNT(Leds);

DallasTemperature *TempSensors[] = {
    &AirTemp
};

uint8_t TempSensorsCount = ARRAY_ITEMS_COUNT(TempSensors);

#endif