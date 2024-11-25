#ifndef ASYNC
#define ASYNC

void addFunctionToQueue(void (*fcnToCall)(), unsigned long milliseconds);
void asyncLoop();

#endif