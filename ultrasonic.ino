#include "LEDStrip.h"

#include "async.h"
#include "speaker.h"
#include "LEDStrip.h"
#include "servo.h"

// setup ultrasonic
const int trigPin = 12;
const int echoPin = 13;
double duration, distance;
float detectionDistance {10.0};

void setupUltrasonic()
{
    // setup ultrasonic
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void ultrasonicLoop()
{
    if (isObjectClose())
    {
        ultrasonicDetected = true;
        queueServoMove();
        queueCountdownAnimation();
        queueCountdown();
        addFunctionToQueue(playerChosen, totalTime); 
    }
    else
    {
        if (ultrasonicDetected)
        {
            ultrasonicDetected = false;
            currentlyCountdown = false;
            currentlyFlashing = false;
            rainbow();
        }
        addFunctionToQueue(ultrasonicLoop, 200); // runs ultrasonicLoop every 200ms (5hz)
    }
}

void playerChosen()
{
    currentlyFlashing = true;
    currentlyCountdown = false;
    disableServo(); // turn servo back off so it doesnt jitter
    queueFlashPlayerChosen();
    addFunctionToQueue(ultrasonicLoop, 5000);
}

// returns a float of what the ultrasonic sensor is currently sensing
float measureUltrasonic()
{
    // create a pulse
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH); // Create a 10 microsecond pulse
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    distance = (((duration * 1000.0) / 340.0) / 100.0) / 2.0; // calculate distance in CM
    Serial.print("Ultrasonic: ");
    Serial.println(distance);
    return distance;
}

// returns true if the ultrasonic sensor is currently at less than half of the
// distance when the arduino initilised
bool isObjectClose()
{
    return (measureUltrasonic() < (detectionDistance));
}

void debugDetectionDistance()
{
    Serial.println(detectionDistance);
}