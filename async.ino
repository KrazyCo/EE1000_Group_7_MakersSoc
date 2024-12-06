constexpr int asyncLength = 128;
unsigned long asyncMillis[asyncLength];
void (*asyncFunctions[asyncLength])(); // arrary of void function pointers

// takes a function pointer and how many milliseconds until it needs to be ran
void addFunctionToQueue(void (*fcnToCall)(), unsigned long milliseconds)
{
    for (int i = 0; i < asyncLength; i++)
    {
        if (!asyncFunctions[i] and asyncMillis[i] == 0) // checking to see if space is free, these should always BOTH either be true or false but idk
        {
            asyncFunctions[i] = fcnToCall; // put the function pointer into the array
            asyncMillis[i] = millis() + milliseconds;
            return; 
        }
    }
    Serial.println("ran out of async spaces - need to increase asyncLength");
}

// main async loop where we check the whole array of async stuff and see if anything is waiting to be ran
void asyncLoop()
{
    for (int i = 0; i < asyncLength; i++)
    {
        if (!asyncFunctions[i] && asyncMillis[i] != 0)
        {
            Serial.println("no function found");
            debugAsync(i);
            debugAsync();
            exit(-1);
        }
        if (asyncFunctions[i] && asyncMillis[i] == 0)
        {
            Serial.println("function found but no time");
            debugAsync(i);
            debugAsync();
            exit(-1);
        }
        if (asyncMillis[i] < millis() and asyncMillis[i] != 0) // if its 0 that means its not used
        {
            if (asyncFunctions[i]) // checking to make sure the function pointer is actually there
            {
                asyncFunctions[i](); 
            }
            else
            {
                Serial.println("function should have been ran but no pointer"); // should never run
                debugAsync(i);
                debugAsync();
                exit(-1);
            }
            asyncFunctions[i] = nullptr; // clear asyncFunctions array at i
            asyncMillis[i] = 0; // clear asyncMillis array at i
        }
    }
}

// no arg for function prints the whole array list
void debugAsync()
{
    Serial.print("\tcurrent millis is ");
    Serial.println(millis());
    for (int i = 0; i < asyncLength; i++)
    {
        Serial.print('\t');
        Serial.print(i);
        Serial.print(": \t");
        Serial.print(asyncMillis[i]);
        Serial.print("ms \t");
        Serial.print((unsigned long)asyncFunctions[i]);
        if (asyncFunctions[i])
        {
            Serial.println("\thas function pointer");
        }
        else
        { 
            Serial.println("\tno function pointer");
        }
    }
}

// function with 1 int arugument prints only that item
void debugAsync(int i)
{
    Serial.print("\tcurrent millis is ");
    Serial.println(millis());
    Serial.print('\t');
    Serial.print(i);
    Serial.print(": \t");
    Serial.print(asyncMillis[i]);
    Serial.print("ms \t");
    Serial.print((unsigned long)asyncFunctions[i]);
    if (asyncFunctions[i])
    {
        Serial.println("\thas function pointer");
    }
    else
    { 
        Serial.println("\tno function pointer");
    }
}