#include <stdio.h>
#define MAX_DATE 100000
int degrees[MAX_DATE] = { 0, };
int lengthOfDegrees;
int dateToSum;
int maxDegree = 0;

void getProperties();
int findMaxDegree();

int main() {
	getProperties();
	maxDegree = findMaxDegree();
	printf("%d", maxDegree);

	return 0;
}


void getProperties() {
	scanf_s("%d ", &lengthOfDegrees);
	scanf_s("%d", &dateToSum);

	for (int i = 0; i < lengthOfDegrees; i++)
		scanf_s("%d", &degrees[i]);
}
int findMaxDegree() {
	int tempMaxDegree = -2000000000;
	int endOfIndex = lengthOfDegrees - dateToSum + 1;

	int tempSum = 0;
	for (int i = 0; i < endOfIndex; i++) {
		if (i == 0)
			for (int j = 0; j < dateToSum; j++) {
				tempSum += degrees[i + j];
			}
		else
			tempSum = tempSum - degrees[i - 1] + degrees[i + dateToSum - 1];
		tempMaxDegree = tempSum > tempMaxDegree ? tempSum : tempMaxDegree;
	}
	return tempMaxDegree;
}
