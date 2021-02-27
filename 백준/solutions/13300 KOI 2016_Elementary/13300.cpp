#include <stdio.h>
#define MAX_STUDENT 1000
#define MAXNUM_INROOM 1000
#define MAX_GRADE 6

int student[MAX_GRADE][2] = { 0, };
int numOfStudent;
int numOfInRoom;

void getProperties();
int getNumOfRoomNeed();

int main() {
	getProperties();
	printf("%d", getNumOfRoomNeed());

	return 0;
}


void getProperties() {
	scanf_s("%d %d", &numOfStudent, &numOfInRoom);

	for (int i = 0; i < numOfStudent; i++) {
		int sex, grade;
		scanf_s("%d %d", &sex, &grade);

		student[grade - 1][sex]++; 
	}
}

int getNumOfRoomNeed() {
	int numOfRoomNeed = 0;

	for (int i = 0; i < MAX_GRADE; i++) {
		for (int j = 0; j < 2; j++) {
			numOfRoomNeed += (student[i][j] / numOfInRoom);
			if (student[i][j] % numOfInRoom != 0)
				numOfRoomNeed++;
		}
	}

	return numOfRoomNeed;
}