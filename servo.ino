#include <Servo.h>

#include "async.h"
#include "speaker.h"
#include "random.h"

// setup servo
const int servoPin = 5;
Servo servo;
#define SERVO_LIST_NUM 64
int servoMoveOutputs[SERVO_LIST_NUM];
int currentServoMove{0};


void setupServo()
{
    // setup servo
    servo.attach(servoPin);
    disableServo(); // disable servo when not needed
}

void writeServo(int amount)
{
    servo.write(amount);
}

void queueServoMove()
{
    int currentAmountOfTime{0};
    int randomNumOutput{0};
    int randomTime{0};
    int i{0};
    currentServoMove = 0;

    enableServo(); // enable servo

    while (currentAmountOfTime < totalTime - 100)
    {
        if (i >= SERVO_LIST_NUM)
        {
            Serial.println("servo list is too short");
            return;
        }
        randomNumOutput = generateRandomNumber(0, 180);
        randomTime = generateRandomNumber(200, 500);
        currentAmountOfTime += randomTime;
        servoMoveOutputs[i] = randomNumOutput;
        addFunctionToQueue(nextServoMovement, currentAmountOfTime);
        Serial.print("servo move ");
        Serial.print(i);
        Serial.print(" in ");
        Serial.print(currentAmountOfTime);
        Serial.print("ms to ");
        Serial.println(randomNumOutput);
        i++;
    }
}

void nextServoMovement()
{
    if (currentServoMove >= SERVO_LIST_NUM)
    {
        Serial.println("somehow ran out of servo list");
        exit(-1);
    }
    writeServo(servoMoveOutputs[currentServoMove]);
    currentServoMove++;
}

void enableServo()
{
    servo.attach(servoPin); // enable servo
}

void disableServo()
{
    servo.detach(); // disable servo
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