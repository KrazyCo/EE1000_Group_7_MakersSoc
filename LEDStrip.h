#ifndef LEDSTRIP
#define LEDSTRIP

void setupLEDStrip();
void LEDTestPattern();
void clearLEDStrip();
void nextFallingAnimation();
void queueFallingAnimation();
void rainbow();
void countdownAnimation();
void queueCountdownAnimation();

bool ultrasonicDetected{false};
bool currentlyCountdown{false};

#endif