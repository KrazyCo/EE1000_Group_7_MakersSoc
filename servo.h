#ifndef SERVO
#define SERVO

void setupServo();
void writeServo(int amount);
void queueServoMove();
void nextServoMovement();
void enableServo();
void disableServo();

#endif