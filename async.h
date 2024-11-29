#ifndef ASYNC
#define ASYNC

void addFunctionToQueue(void (*fcnToCall)(), unsigned long milliseconds);
void asyncLoop();
void debugAsync();
void debugAsync(int i);

#endif