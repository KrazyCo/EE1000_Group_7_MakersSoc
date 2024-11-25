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

// todo: implement main loop async for different components
// todo: make animations for led strips

void setup()
{
    Serial.begin(115200);

    setupServo();
    setupUltrasonic();
    setupLEDStrip();
    setupLDR();
}

void loop()
{
    writeServo(0);
    Serial.println("servo forwards");
    Serial.println(measureUltrasonic());
    Serial.println(measureLDR());
    Serial.println(isObjectClose());
    ultrasonicLoop();
    delay(1000);
    writeServo(180);
    Serial.println("servo stop");
    Serial.println(measureUltrasonic());
    Serial.println(measureLDR());
    Serial.println(isObjectClose());
    ultrasonicLoop();
    delay(1000);
}
