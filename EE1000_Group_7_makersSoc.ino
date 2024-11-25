#include <Servo.h>
#include <FastLED.h>

#include "async.h"

// *pin d3: 360 degree servo data
// *pin d9: led strip data
// *pin d12: ultrasonic trig line
// *pin d13: ultrasonic echo line

// *pin a0: LDR line
// !pin a1: speaker line

// todo: see if can set ldr pin to a uint8_t to have it in a variable pointer
// todo: fix startDistance to change on startup as couldnt figure out the bug where startDistance gets set to 128.00 after first activation
// todo: make main loop async for different components
// todo: make animations for led strips

// setup servo
const int servoPin = 3;
Servo servo;

// setup ultrasonic
const int trigPin = 12;
const int echoPin = 13;
double duration, distance;
float startDistance;

// setup LED strip
#define LED_PIN 9
#define NUM_LEDS 30
CRGB leds[NUM_LEDS];
int i{};
int brightness{50};

// debug variables
int debugCount{0};

void setup()
{
    Serial.begin(115200);

    // setup servo
    servo.attach(servoPin);

    // setup ultrasonic
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    startDistance = measureUltrasonic();

    // setup LDR
    pinMode(A0, INPUT);

    // setup LED strip
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void loop()
{
    // servo.write(180);
    Serial.println("servo forwards");
    Serial.println(measureUltrasonic());
    Serial.println(measureLDR());
    Serial.println(startDistance);
    Serial.println(isObjectClose());
    ultrasonicLoop();
    delay(1000);
    // servo.write(0);
    Serial.println("servo stop");
    Serial.println(measureUltrasonic());
    Serial.println(measureLDR());
    Serial.println(startDistance);
    Serial.println(isObjectClose());
    ultrasonicLoop();
    delay(1000);
}

void ultrasonicLoop()
{
    if (isObjectClose())
    {
        LEDTestPattern();
    }
    else
    {
        clearLEDStrip();
    }
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
    return distance;
}

// returns the value (0-1023) of the LDR
int measureLDR()
{
    return analogRead(A0);
}

// sets the LED strip to the test pattern
void LEDTestPattern()
{
    for (int i = 0; i <= NUM_LEDS; i++)
    {
        debugStartDistance();
        if (i < 5)
        {
            leds[i] = CRGB(0, 0, 255);
            debugStartDistance();
        }
        else if (i < 10)
        {
            leds[i] = CRGB(255, 0, 255);
            debugStartDistance();
        }
        else if (i < 15)
        {
            leds[i] = CRGB(255, 0, 0);
            debugStartDistance();
        }
        else if (i < 20)
        {
            leds[i] = CRGB(255, 255, 0);
            debugStartDistance();
        }
        else if (i < 25)
        {
            leds[i] = CRGB(0, 255, 0);
            debugStartDistance();
        }
        else if (i <= 30)
        {
            leds[i] = CRGB(255, 255, 255);
            debugStartDistance();
        }
        FastLED.show();
    }
}

// sets the LED strip to all off
void clearLEDStrip()
{
    for (int i = 0; i <= NUM_LEDS; i++)
        leds[i] = CRGB(0, 0, 0);
    FastLED.show();
}

// returns true if the ultrasonic sensor is currently at less than half of the
// distance when the arduino initilised
bool isObjectClose()
{
    return (measureUltrasonic() < (startDistance / 1.1));
}

void debugStartDistance()
{
    Serial.print(debugCount);
    Serial.print(": ");
    Serial.println(startDistance);
}