#ifndef SERVO
#define SERVO

void setupServo();
void writeServo(int amount);
void servo0();
void servo180();
void queueServoMove();
void nextServoMovement();

#endif