#include <stdio.h>
#define NUM_OF_ROUND 10
int cardsOfA[NUM_OF_ROUND];
int cardsOfB[NUM_OF_ROUND];
int scoreA = 0;
int scoreB = 0;
int numOfDraw = 0;
int lastWin = 0;
int winner = 0;

void getProperties();
void playGame();

int main() {
	getProperties();
	playGame();

	return 0;
}

void getProperties() {
	for (int i = 0; i < NUM_OF_ROUND; i++) {
		scanf_s("%d ", &cardsOfA[i]);
	}
	for (int i = 0; i < NUM_OF_ROUND; i++) {
		scanf_s("%d", &cardsOfB[i]);
	}
}
void playGame() {
	for (int i = 0; i < NUM_OF_ROUND; i++) {
		if (cardsOfA[i] > cardsOfB[i]) {
			scoreA += 3;
			lastWin = 1;
		}
		else if (cardsOfA[i] < cardsOfB[i]) {
			scoreB += 3;
			lastWin = -1;
		}
		else {
			scoreA++;
			scoreB++;
			numOfDraw++;
		}
	}

	printf("%d %d", scoreA, scoreB);

	if (scoreA > scoreB)
		printf("A");
	else if (scoreA < scoreB)
		printf("B");
	else {
		if (numOfDraw == NUM_OF_ROUND)
			printf("D");
		else if (lastWin == 1)
			printf("A");
		else if (lastWin == -1)
			printf("B");
	}
	
}
