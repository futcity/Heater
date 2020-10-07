/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include "ports.h"
#include "common.h"
#include "heater.h"
#include "boards.h"

WidgetLED LedStatus(Blynk);
WidgetLED LedHeater(Blynk);

WidgetLED *LedWidgets[] = {
    &LedStatus,
    &LedHeater
};

uint8_t LedWidgetsCount = ARRAY_ITEMS_COUNT(LedWidgets);

void PortsInit()
{
    LedStatus.setVPin(VP_LED_STATUS);
    LedHeater.setVPin(VP_LED_HEATER);
}

BLYNK_CONNECTED()
{
    Blynk.syncAll();
}

BLYNK_WRITE(VP_STATUS_SWITCH)
{
    if (param.asInt() == TRUE) {
        HeaterSetStatus(true);
    } else {
        HeaterSetStatus(false);
    }
    HeaterUpdate();
}

BLYNK_WRITE(VP_THRESHOLD)
{
    HeaterSetThreshold(param.asInt());
}

BLYNK_WRITE(VP_EXT_THRESHOLD)
{
    HeaterSetExtThreshold(param.asInt());
}
