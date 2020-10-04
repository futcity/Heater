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

WidgetLED LedStatus(Blynk);
WidgetLED LedHeater(Blynk);

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
        Status = true;
    } else {
        Status = false;
    }

    HeaterUpdate(Status);
}

BLYNK_WRITE(VP_THRESHOLD)
{
    Threshold = param.asInt();
}
