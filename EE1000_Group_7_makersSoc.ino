#include "async.h"

#include "servo.h"
#include "ultrasonic.h"
#include "LEDStrip.h"
#include "LDR.h"
#include "speaker.h"

// *pin d3: 360 degree servo data
// *pin d9: led strip data
// *pin d12: ultrasonic trig line
// *pin d13: ultrasonic echo line

// *pin a0: LDR line
// *pin a1: speaker line

// todo: fix the melody for the 3rd section
// todo: once the contiunius servo is being used make sure that the current servo code works with it - will probs have to give it longer time between steps

void setup()
{
    Serial.begin(115200);

    // setup each component
    setupServo();
    setupUltrasonic();
    setupLEDStrip();
    setupLDR();
    setupSpeaker();

    // setup starting functions
    addFunctionToQueue(LDRLoop, 100);
    addFunctionToQueue(ultrasonicLoop, 100);
    addFunctionToQueue(rainbow, 100);
    // addFunctionToQueue(servo0, 1000);
    // addFunctionToQueue(queueCountdown, 1000);
    // addFunctionToQueue(queueFallingAnimation, 1000);
}

void loop()
{
    asyncLoop();
    // delay(100);
}
