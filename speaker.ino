#include "async.h"

#include "speaker.h"

#define SPEAKER_PIN 6

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

constexpr int countdownNotes{sizeof(countdownTone) / sizeof(countdownTone[0])};
int currentTone{0};

void setupSpeaker()
{
    for (int i = 0; i < countdownNotes; i++)
    {
        totalTime += countdownToneTime[i];
    }
}

void nextCountdownTone()
{
    Serial.print("nextCountdownTone ");
    Serial.print(countdownTone[currentTone]);
    Serial.print("hz for ");
    Serial.print(countdownToneTime[currentTone]);
    Serial.println("ms");
    if (currentTone < countdownNotes)
    {
        tone(SPEAKER_PIN, countdownTone[currentTone], countdownToneTime[currentTone]);
        currentTone++;
    }
    else
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
        addFunctionToQueue(nextCountdownTone, cumulativeTime);
        cumulativeTime += countdownToneTime[i];
    }
}

void speakerTest()
{

    // David's music: 'Lab Tune 1' ...

    int freq{500};
    tone(A1, freq, 400);
    delay(400);
    tone(A1, freq * (5.0 / 4.0), 200);
    delay(200);
    tone(A1, freq * (3.0 / 2.0), 200);
    delay(250);
    tone(A1, freq * (5.0 / 3.0), 400);
    delay(400);
    tone(A1, freq * (3.0 / 2.0), 400);
    delay(400);
    tone(A1, freq * (5.0 / 4.0), 200);
    delay(200);
    tone(A1, freq, 200);
    delay(200);
    tone(A1, freq * (3.0 / 2.0), 400);
    delay(500);
}