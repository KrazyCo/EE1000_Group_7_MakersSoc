#include "async.h"

#include "speaker.h"

#define SPEAKER_PIN 6

// the lists of tones and times to be played when the ultrasonic sensor detects something
constexpr int countdownTone[]{
    NOTE_C4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_G4,
    NOTE_C4, NOTE_C5, NOTE_G4, NOTE_AS4, NOTE_A4, NOTE_G4,
    NOTE_C4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4,
    NOTE_C5, NOTE_AS4, 0, NOTE_F4, NOTE_G4, 0, NOTE_F5, NOTE_DS5, NOTE_C5, NOTE_DS5};
constexpr int countdownToneTime[]{
    375, 375, 250, 375, 375, 250,
    375, 375, 250, 375, 375, 250,
    375, 375, 250, 375, 375, 250,
    125, 125, 250, 125, 125, 250, 125, 125, 125, 125};

// figure out the number of tones in the list
constexpr int countdownNotes{sizeof(countdownTone) / sizeof(countdownTone[0])};
int currentTone{0}; // using as a global variable

// setup the speaker
void setupSpeaker()
{
    for (int i = 0; i < countdownNotes; i++)
    {
        totalTime += countdownToneTime[i]; // calculate the total time it takes for the song to play to be used by other functions
    }
}

void nextCountdownTone()
{
    Serial.print("nextCountdownTone ");
    Serial.print(countdownTone[currentTone]);
    Serial.print("hz for ");
    Serial.print(countdownToneTime[currentTone]);
    Serial.println("ms");

    if (currentTone < countdownNotes) // if there are still tones to play
    {
        tone(SPEAKER_PIN, countdownTone[currentTone], countdownToneTime[currentTone]-10); // play the tone
        currentTone++;
    }
    else // otherwise reset the tone count to the start
    {
        currentTone = 0;
    }
}

void queueCountdown()
{
    currentTone = 0;
    int cumulativeTime{0};
    for (int i = 0; i < countdownNotes; i++)
    {
        addFunctionToQueue(nextCountdownTone, cumulativeTime); // add the tone to the queue to be played in the correct time
        cumulativeTime += countdownToneTime[i];                // add the time to the cumulative time
    }
}