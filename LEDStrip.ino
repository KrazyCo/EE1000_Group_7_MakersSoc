#include <FastLED.h>

// setup LED strip
#define LED_PIN 9
#define NUM_LEDS 30
CRGB leds[NUM_LEDS];
int i{};
int brightness{50};

void setupLEDStrip()
{
    // setup LED strip
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
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
