void setupLDR()
{
    // setup LDR
    pinMode(A0, INPUT);
}

// returns the value (0-1023) of the LDR
int measureLDR()
{
    return analogRead(A0);
}