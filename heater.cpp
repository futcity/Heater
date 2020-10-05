/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "heater.h"
#include "boards.h"
#include "ports.h"
#include "common.h"

bool Status = false;
uint8_t Threshold = 25;

/*
 * Private functions
 */

static int8_t ReadTemp()
{
    TempSensors[AIR_SENSOR]->requestTemperatures();
    return TempSensors[AIR_SENSOR]->getTempCByIndex(DEFAULT_SENSOR);
}

/*
 * Public functions
 */

uint8_t HeaterGetThreshold()
{
    return Threshold;
}

void HeaterSetThreshold(uint8_t val)
{
    Threshold = val;
}

bool HeaterGetStatus()
{
    return Status;
}

void HeaterSetStatus(bool val)
{
    Status = val;
}

void HeaterSwitchStatus()
{
    Status = !Status;
}

void HeaterUpdate()
{
    int8_t curTemp;
        
    for (uint8_t i = 0; i < TEMP_RETRIES; i++) {
        curTemp = ReadTemp();
        if (curTemp != TEMP_ERR_VAL)
            break;
        delay(1000);
    }

    Blynk.virtualWrite(VP_CUR_TEMP, curTemp);

    if (curTemp == TEMP_ERR_VAL) {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
        return;
    }

    if (HeaterGetStatus()) {
        /*
         * Control air temperature
         */
        if (curTemp < Threshold) {
            digitalWrite(Relays[HEATER_RELAY], HIGH);
            LedWidgets[HEATER_LED_WIDGET]->on();
        } else {
            digitalWrite(Relays[HEATER_RELAY], LOW);
            LedWidgets[HEATER_LED_WIDGET]->off();
        }

        digitalWrite(Leds[STATUS_LED], LOW);
        LedWidgets[STATUS_LED_WIDGET]->on();
    } else {
        for (uint8_t i = 0; i < RelaysCount; i++) {
            digitalWrite(Relays[i], LOW);
        }
        for (uint8_t i = 0; i < LedsCount; i++) {
            digitalWrite(Leds[i], HIGH);
        }
        for (uint8_t i = 0; i < LedWidgetsCount; i++) {
            LedWidgets[i]->off();
        }
    }
}
