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
    // functions are queued to run in 100ms from startup to allow for any setup to complete
    addFunctionToQueue(LDRLoop, 100);
    addFunctionToQueue(ultrasonicLoop, 100);
    addFunctionToQueue(rainbow, 100);
}

void loop()
{
    asyncLoop();
    delay(10); // stop loop running too fast as speaker breaks
}
