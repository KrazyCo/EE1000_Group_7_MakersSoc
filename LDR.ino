#include <FastLED.h>

#include "async.h"

#define LDR_PIN A0

void setupLDR()
{
    // setup LDR
    pinMode(LDR_PIN, INPUT);
}

// returns the value (0-1023) of the LDR
int measureLDR()
{
    int LDRValue{analogRead(LDR_PIN)};
    // Serial.print("LDR: ");
    // Serial.println(LDRValue);
    return LDRValue;
}

void LDRLoop()
{
    int brightness{min(map(measureLDR(), 500, 1023, 50, 5), 50)};

    Serial.print("brightness: ");
    Serial.println(brightness);

    FastLED.setBrightness(brightness); // set the brightness of the LEDs

    addFunctionToQueue(LDRLoop, 100); // queue this function again in 100ms
}