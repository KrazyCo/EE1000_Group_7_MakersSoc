#include <FastLED.h>

#include "async.h"
#include "LEDStrip.h"

// setup LED strip
#define LED_PIN 9
#define NUM_LEDS 13

CRGB leds[NUM_LEDS];
#define INITIAL_BRIGHTNESS 50

void setupLEDStrip()
{
    // setup LED strip
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(INITIAL_BRIGHTNESS); // this will be overwritten by the LDR loop later
}


int rainbowInitialHue{0};
// rainbow animation
void rainbow()
{
    if (!ultrasonicDetected) // if the ultrasonic sensor detects something stop this loop
    {
        fill_rainbow(leds, NUM_LEDS, rainbowInitialHue, 7); // fill the strip with rainbow colors
        FastLED.show();

        rainbowInitialHue += 5; // increment the hue to make the ranbow seem to move down the strip
        if (rainbowInitialHue > 255) // if the hue is greater than 255 reset it to 0 + anything left over from the previous increment
            rainbowInitialHue -= 255;
        
        addFunctionToQueue(rainbow, 20); // add this function to the queue to be ran in 20ms
    }
}

int countdownLED{0};
void countdownAnimation()
{
    if (currentlyCountdown) // if the countdown is still happening, otherwise break out and dont add to queue again
    {
        if (countdownLED < NUM_LEDS)
        {
            leds[countdownLED] = CRGB(0, 0, 255); // blue LED
            leds[NUM_LEDS - countdownLED-1] = CRGB(255, 213, 0); // yellow LED
            FastLED.show();
            countdownLED++;
        }
        else // if reached the end of the LED strip, start again
        {
            countdownLED = 0;
        }
        addFunctionToQueue(countdownAnimation, 100);
    }
}

// queue the countdown animation to be ran on the next loop
void queueCountdownAnimation()
{
    countdownLED = 0;
    currentlyCountdown = true; // set the countdown flag to true, to be set to false when the countdown is finished
    addFunctionToQueue(countdownAnimation, 0); // add the countdown animation to the queue to be ran on next loop
}

int flashNumber{0}; // flashNumber will be either 0 or 1, alternating between the two to flash the colours
void flashPlayerChosen()
{
    if (currentlyFlashing) // if the LED strip should be flashing, otherwise break out and dont add to queue again
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (i % 2 == flashNumber) // gets alternating LEDs and sets to blue
            {
                leds[i] = CRGB(0, 0, 255); // blue LEDs
            }
            else // sets the other LEDs to yellow
            {
                leds[i] = CRGB(255, 213, 0); // yellow LEDs
            }
        }
        FastLED.show();
        flashNumber = (flashNumber == 0) ? 1 : 0; // if flashNumber is 0, set to 1, otherwise set to 0 

        Serial.print("flashNumber: ");
        Serial.println(flashNumber);

        addFunctionToQueue(flashPlayerChosen, 200); // add this function to the queue to be ran in 200ms so the strip flashes every 200ms
    }
}

// queue the flash animation to be ran on the next loop
void queueFlashPlayerChosen()
{
    flashNumber = 0;
    currentlyFlashing = true; // set the flashing flag to true, to be set to false when the flashing is finished
    addFunctionToQueue(flashPlayerChosen, 0); // add the flash animation to the queue to be ran on next loop
}