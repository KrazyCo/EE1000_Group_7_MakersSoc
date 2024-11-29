#include <Servo.h>
#include "async.h"

// setup servo
const int servoPin = 3;
Servo servo;

void setupServo()
{
    // setup servo
    servo.attach(servoPin);
}

void writeServo(int amount)
{
    servo.write(amount);
}

void servo0()
{
    Serial.println("servo 0");
    writeServo(0);
    addFunctionToQueue(servo180, 1000); 
}

void servo180()
{
    Serial.println("servo 180");
    writeServo(180);
    addFunctionToQueue(servo0, 1000); 
}