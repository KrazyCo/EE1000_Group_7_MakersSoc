#include <Servo.h>

#include "async.h"
#include "speaker.h"
#include "random.h"

// setup servo
#define SERVO_PIN 5

Servo servo;
#define SERVO_LIST_NUM 64
int servoMoveOutputs[SERVO_LIST_NUM];
int currentServoMove{0};


void setupServo()
{
    // setup servo
    servo.attach(SERVO_PIN);
    disableServo(); // disable servo so that it doesnt jitter due to arduino timing problems
}

// moves servo to set amount
void writeServo(int amount)
{
    servo.write(amount);
}

// randomises the servo movements and adds them to the queue up to the time that it takes for the song to play
void queueServoMove()
{
    int currentAmountOfTime{0};
    int randomNumOutput{0};
    int randomTime{0};
    int i{0};
    currentServoMove = 0;

    enableServo(); // enable servo

    // keeps queueing movments up to the time that the song plays - 100ms to allow for the servo to finish moving
    while (currentAmountOfTime < totalTime - 100) // totalTime is from speaker.h and is the time it takes for the song to play
    {
        if (i >= SERVO_LIST_NUM) // error handling so that dont overrun the servo list
        {
            Serial.println("servo list is too short");
            return;
        }
        // generates the random move and random time
        randomNumOutput = generateRandomNumber(0, 180);
        randomTime = generateRandomNumber(200, 500);

        // adds the random time to the current time
        currentAmountOfTime += randomTime;

        // adds the random move to the servo list to be ran using the nextServoMovement function
        servoMoveOutputs[i] = randomNumOutput;

        // adds the random move to the queue to be ran in the generated random time
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
        Serial.println("somehow ran out of servo list"); // error handling so that dont overrun the servo list
        // exit(-1); // this shouldnt happens so exit the program to help with debugging if it does, but commeting out for production
    }
    // moves the servo to the next position in the list
    writeServo(servoMoveOutputs[currentServoMove]);
    currentServoMove++;
}

// as we are disabling the servo to stop jittering, we need to enable it before we use it
void enableServo()
{
    servo.attach(SERVO_PIN); // enable servo
}

// disable the servo to stop jittering
void disableServo()
{
    servo.detach(); // disable servo
}