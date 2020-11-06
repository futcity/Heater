/*
 * Future City Project
 *
 * Copyright (C) 2020 Sergey Denisov. GPLv3
 *
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 */

#include <ESP8266WiFi.h>

#include "ports.h"
#include "boards.h"
#include "common.h"
#include "heater.h"

#define MAIN_TMR_DELAY  1000

SimpleTimer MainTimer;

static void ReadButton()
{
    if (digitalRead(Buttons[MAIN_BUTTON]) == LOW) {
        HeaterSwitchStatus();
        HeaterUpdate();
        Blynk.virtualWrite(VP_STATUS_SWITCH, (int)HeaterGetStatus());
        delay(600);
    }
}

static void MainTimerCallback()
{
    HeaterUpdate();
}

void setup()
{
    BoardInit();
    PortsInit();
    Blynk.begin(DEVICE_KEY, WIFI_SSID, WIFI_PASSWD, BLYNK_SERVER, BLYNK_SERVER_PORT);
    MainTimer.setInterval(MAIN_TMR_DELAY, MainTimerCallback);
}

void loop()
{
    Blynk.run();
    ReadButton();
    MainTimer.run();
}
