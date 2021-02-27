#include <stdio.h>
#define MAX_LENGTH 30
int arrInput[MAX_LENGTH] = { 0, };
int arrOutput[MAX_LENGTH] = { 0, };
int arrLength;


void getProperties();
bool decipheringInputToOutput();
void print();

int main() {
	getProperties();
	if(decipheringInputToOutput())
		printf("-1");
	else
		print();
}

void getProperties() {
	scanf_s("%d", &arrLength);
	for (int i = 0; i < arrLength; i++)
		scanf_s("%d", &arrInput[i]);
}

bool decipheringInputToOutput() {
	arrOutput[0] = arrInput[0];
	int exIndex = 0;
	int exValue = arrInput[0];
	int currentIndex = -1;
	bool isThereInputFile = false;


	for (int i = 1; i < arrLength; i++) {
		if (isThereInputFile)
			break;
		currentIndex = (exIndex + exValue) % arrLength;

		int whileTimes = 0;
		while (arrOutput[currentIndex] != 0) {
			if (whileTimes > arrLength) {
				isThereInputFile = true;
				break;
			}
			currentIndex = (currentIndex + 1) % arrLength;
			whileTimes++;
		}

		arrOutput[currentIndex] = arrInput[i];
		exIndex = currentIndex;
		exValue = arrInput[i];
	}

	return isThereInputFile;
}

void print() {
	printf("%d\n", arrLength);
	for (int i = 0; i < arrLength; i++)
		printf("%d ", arrOutput[i]);
}