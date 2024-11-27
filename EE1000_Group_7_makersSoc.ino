#include "async.h"

#include "servo.h"
#include "ultrasonic.h"
#include "LEDStrip.h"
#include "LDR.h"

// *pin d3: 360 degree servo data
// *pin d9: led strip data
// *pin d12: ultrasonic trig line
// *pin d13: ultrasonic echo line

// *pin a0: LDR line
// !pin a1: speaker line

// todo: make animations for led strips
// todo: make led animations work with async functions
// todo: figure out what needs to happen to the main ultrasonic loop

// ? everything is waiting on led animation rn, so either need to do those or make some debug ones for rn

void setup()
{
    Serial.begin(115200);

    // setup each component
    setupServo();
    setupUltrasonic();
    setupLEDStrip();
    setupLDR();

    // setup starting functions
    addFunctionToQueue(ultrasonicLoop, 1000);
}

void loop()
{
    asyncLoop();
}
