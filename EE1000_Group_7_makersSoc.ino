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

// todo: make the LDR change the brightness, needs to be a log curve probs to make it looks good 

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
    addFunctionToQueue(LDRLoop, 1000);
    addFunctionToQueue(ultrasonicLoop, 1000);
    // addFunctionToQueue(servo0, 1000);
    // addFunctionToQueue(queueCountdown, 1000);
    // addFunctionToQueue(queueFallingAnimation, 1000);
    addFunctionToQueue(rainbow, 1000);
}

void loop()
{
    asyncLoop();
    // delay(100);
}
