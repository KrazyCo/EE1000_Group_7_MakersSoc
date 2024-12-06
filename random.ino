void setupRandom()
{
    // setup random number generator
	randomSeed(analogRead(A7)); // seed random num gen using analog pin A7 which is floating
}

// generates a random number between startNum and endNum
int generateRandomNumber(int startNum, int endNum) {
	return random(startNum, endNum);
}