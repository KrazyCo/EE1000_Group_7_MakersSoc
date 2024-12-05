#include <FastLED.h>

#include "async.h"
#include "LEDStrip.h"

// setup LED strip
#define LED_PIN 9
#define NUM_LEDS 13
CRGB leds[NUM_LEDS];
int i{};
int brightness{50};
// bool ultrasonicDetected{false};

void setupLEDStrip()
{
    // setup LED strip
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

// constexpr int fallingAnimations {5};
int currentFallingLed{0};

void nextFallingAnimation()
{
    if (currentFallingLed < NUM_LEDS)
    {
        leds[currentFallingLed] = CRGB(0, 0, 255);
        FastLED.show();
        currentFallingLed++;
    }
    else
    {
        currentFallingLed = 0;
    }
}

void queueFallingAnimation()
{
    int timeBetweenAnimations{50};
    int cumulativeTime{0};
    for (int i = 0; i < NUM_LEDS; i++)
    {
        addFunctionToQueue(nextFallingAnimation, cumulativeTime);
        cumulativeTime += timeBetweenAnimations;
    }
}

int rainbowInitialHue{0};
// rainbow animation
void rainbow()
{
    if (!ultrasonicDetected)
    {
        fill_rainbow(leds, NUM_LEDS, rainbowInitialHue, 7);
        FastLED.show();
        rainbowInitialHue += 5;
        if (rainbowInitialHue > 255)
            rainbowInitialHue -= 255;
        addFunctionToQueue(rainbow, 20);
    }
}

int countdownLED{0};
void countdownAnimation()
{
    if (currentlyCountdown)
    {
        if (countdownLED < NUM_LEDS)
        {
            leds[countdownLED] = CRGB(0, 0, 255);
            leds[NUM_LEDS - countdownLED-1] = CRGB(255, 213, 0);
            FastLED.show();
            Serial.print("countdownLED: ");
            Serial.print(countdownLED);
            Serial.print(" NUM_LEDS - countdownLED: ");
            Serial.println(NUM_LEDS - countdownLED-1);
            countdownLED++;
        }
        else
        {
            countdownLED = 0;
        }
        addFunctionToQueue(countdownAnimation, 100);
    }
}

void queueCountdownAnimation()
{
    countdownLED = 0;
    currentlyCountdown = true;
    addFunctionToQueue(countdownAnimation, 0);
}

// sets the LED strip to the test pattern
void LEDTestPattern()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (i < 5)
        {
            leds[i] = CRGB(0, 0, 255);
        }
        else if (i < 10)
        {
            leds[i] = CRGB(255, 0, 255);
        }
        else if (i < 15)
        {
            leds[i] = CRGB(255, 0, 0);
        }
        else if (i < 20)
        {
            leds[i] = CRGB(255, 255, 0);
        }
        else if (i < 25)
        {
            leds[i] = CRGB(0, 255, 0);
        }
        else if (i <= 30)
        {
            leds[i] = CRGB(255, 255, 255);
        }
        FastLED.show();
    }
}

// sets the LED strip to all off
void clearLEDStrip()
{
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CRGB(0, 0, 0);
    FastLED.show();
}
