#include <FastLED.h>

#include "async.h"

void setupLDR()
{
    // setup LDR
    pinMode(A0, INPUT);
}

// returns the value (0-1023) of the LDR
int measureLDR()
{
    int LDRValue{analogRead(A0)};
    // Serial.print("LDR: ");
    // Serial.println(LDRValue);
    return LDRValue;
}

void LDRLoop()
{
    int brightness{min(map(measureLDR(), 500, 1023, 50, 5), 50)};
    Serial.print("brightness: ");
    Serial.println(brightness);
    FastLED.setBrightness(brightness);
    addFunctionToQueue(LDRLoop, 100);
}