#include "LEDStrip.h"

#include "async.h"
#include "speaker.h"
#include "LEDStrip.h"
#include "servo.h"

// setup ultrasonic pins
#define TRIG_PIN 12
#define ECHO_PIN 13

float detectionDistance{4.0};

double duration, distance;

void setupUltrasonic()
{
    // setup ultrasonic
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void ultrasonicLoop()
{
    if (ultrasonicDetected) // if this is the first time the loop has ran since it detected something
    {
        ultrasonicDetected = false;
        currentlyCountdown = false;
        currentlyFlashing = false;
        rainbow(); // start up the idle rainbow animation
    }
    if (isObjectClose()) // if the ultrasonic sensor detects something
    {
        ultrasonicDetected = true;                   // sets the flag to true so that  the rainbow animation stops
        queueServoMove();                            // queue the servo movements
        queueCountdownAnimation();                   // queue the countdown animation on the LED strip
        queueCountdown();                            // queue the countdown tones
        addFunctionToQueue(playerChosen, totalTime); // queue the player chosen function to be ran after the countdown has finished
    }
    else
    {
        addFunctionToQueue(ultrasonicLoop, 100); // runs ultrasonicLoop every 200ms (5hz)
    }
}

// function to be ran when the player is chosen
void playerChosen()
{
    currentlyFlashing = true;   // set the flag to true so that the LED strip flashes
    currentlyCountdown = false; // set the flag to false so that the countdown stops
    disableServo();             // turn servo back off so it doesnt jitter
    queueFlashPlayerChosen();
    addFunctionToQueue(ultrasonicLoop, 5000); // restart the ultrasonic loop after 5 seconds
}

// returns a float of what the ultrasonic sensor is currently sensing
float measureUltrasonic()
{
    // create a pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH); // Create a 10 microsecond pulse
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);
    duration = pulseIn(ECHO_PIN, HIGH);

    distance = (((duration * 1000.0) / 340.0) / 100.0) / 2.0; // calculate distance in CM

    Serial.print("Ultrasonic: ");
    Serial.println(distance);

    return distance;
}

// returns true if the ultrasonic sensor is currently less than the defined detection distance
bool isObjectClose()
{
    return (measureUltrasonic() < (detectionDistance));
}