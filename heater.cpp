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

static int8_t ReadTemp()
{
    TempSensor.requestTemperatures();
    return TempSensor.getTempCByIndex(DEFAULT_SENSOR);
}

void HeaterUpdate(bool status)
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
        digitalWrite(Relay, LOW);
        LedHeater.off();
        return;
    }

    if (status) {
        if (curTemp < Threshold) {
            digitalWrite(Relay, HIGH);
            LedHeater.on();
        } else {
            digitalWrite(Relay, LOW);
            LedHeater.off();
        }
        digitalWrite(Led, LOW);
        LedStatus.on();
    } else {
        digitalWrite(Relay, LOW);
        digitalWrite(Led, HIGH);
        LedStatus.off();
        LedHeater.off();
    }
}