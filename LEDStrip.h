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
void flashPlayerChosen();
void queueFlashPlayerChosen();

bool ultrasonicDetected{false};
bool currentlyCountdown{false};
bool currentlyFlashing{false};

#endif