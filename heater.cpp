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
uint8_t ExtThreshold = 25;

/*
 * Private functions
 */

static int8_t ReadTemp(uint8_t k)
{
    TempSensors[k]->requestTemperatures();
    return TempSensors[k]->getTempCByIndex(DEFAULT_SENSOR);
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

uint8_t HeaterGetExtThreshold()
{
    return ExtThreshold;
}

void HeaterSetExtThreshold(uint8_t val)
{
    ExtThreshold = val;
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
    int8_t curTemp[TempSensorsCount];
    bool state;

    for (uint8_t j = 0; j < TEMP_RETRIES; j++) {
        curTemp[MAIN_SENSOR] = ReadTemp(MAIN_SENSOR);
        if (curTemp[MAIN_SENSOR] != TEMP_ERR_VAL)
            break;
        delay(100);
    }
#ifdef WARM_FLOOR_DEVICE
    for (uint8_t j = 0; j < TEMP_RETRIES; j++) {
        curTemp[EXT_SENSOR] = ReadTemp(EXT_SENSOR);
        if (curTemp[EXT_SENSOR] != TEMP_ERR_VAL)
            break;
        delay(100);
    }
#endif

    Blynk.virtualWrite(VP_CUR_TEMP, curTemp[MAIN_SENSOR]);
#ifdef WARM_FLOOR_DEVICE
    Blynk.virtualWrite(VP_CUR_EXT_TEMP, curTemp[EXT_SENSOR]);
#endif

    if (curTemp[MAIN_SENSOR] == TEMP_ERR_VAL) {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
        return;
    }
#ifdef WARM_FLOOR_DEVICE
    if (curTemp[EXT_SENSOR] == TEMP_ERR_VAL) {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
        return;
    }
#endif

    /*
     * Update status
     */
    if (HeaterGetStatus()) {
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
        return;
    }

#ifdef WARM_FLOOR_DEVICE
    /*
        * Control main & extended temperature
        */
    if ((curTemp[EXT_SENSOR] <= HeaterGetExtThreshold()) &&
        (curTemp[MAIN_SENSOR]) <= HeaterGetThreshold())
    {
        digitalWrite(Relays[HEATER_RELAY], HIGH);
        LedWidgets[HEATER_LED_WIDGET]->on();
    } else {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
    }
#else
    /*
    * Control main temperature
    */
    if (curTemp[MAIN_SENSOR] < HeaterGetThreshold()) {
        digitalWrite(Relays[HEATER_RELAY], HIGH);
        LedWidgets[HEATER_LED_WIDGET]->on();
    } else {
        digitalWrite(Relays[HEATER_RELAY], LOW);
        LedWidgets[HEATER_LED_WIDGET]->off();
    }
#endif
}
