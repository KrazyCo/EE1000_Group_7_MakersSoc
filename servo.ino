#include <Servo.h>

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