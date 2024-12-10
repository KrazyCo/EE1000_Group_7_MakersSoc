#ifndef LEDSTRIP
#define LEDSTRIP

void setupLEDStrip();
void rainbow();
void countdownAnimation();
void queueCountdownAnimation();
void flashPlayerChosen();
void queueFlashPlayerChosen();

bool ultrasonicDetected{false};
bool currentlyCountdown{false};
bool currentlyFlashing{false};

#endif