void setupSpeaker()
{
    return;
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