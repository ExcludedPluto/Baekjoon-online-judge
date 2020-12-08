#include <stdio.h>
#define MAXNUM_APARTMENT 30000
#define MAXNUM_CAPACITY_BUS 2000
#define FAREST_APARTMENT 100000
#define MAX_RANGE_BUS 1000000000

typedef struct apartment {
	int location;
	int numOfStudent;
} apartment;

int numOfApartment;
int capacityOfBus;
int pointOfSchool;
apartment aparts[MAXNUM_APARTMENT];
int minimumRange = 0;



void getProperties();
void sort();
void findMinimumRange();
int findPointsOfSchoolOnArray();

int main() {
	getProperties();
	sort();
	findMinimumRange();
	printf("%d", minimumRange);
}

void getProperties() {
	scanf_s("%d %d %d", &numOfApartment, &capacityOfBus, &pointOfSchool);

	for (int i = 0; i < numOfApartment; i++) {
		scanf_s("%d %d", &aparts[i].location, &aparts[i].numOfStudent);
	}
}

void sort() {
	for (int i = 0; i < numOfApartment; i++) {
		int tempMin = i;
		for (int j = i+1; j < numOfApartment; j++) {
			if (aparts[tempMin].location > aparts[j].location)
				tempMin = j;
		}
		apartment temp = aparts[i];
		aparts[i] = aparts[tempMin];
		aparts[tempMin] = temp;
	}
}

void findMinimumRange() {
	int pointOfSchoolOnArray = findPointsOfSchoolOnArray();

	int tempCapacityBus = capacityOfBus;
	bool isOnWay = true;
	for (int i = 0; i < pointOfSchoolOnArray; i++) {
		if (isOnWay) {
			minimumRange += 2 * (pointOfSchool - aparts[i].location);
			isOnWay = false;
		}
		tempCapacityBus -= aparts[i].numOfStudent;
		if (tempCapacityBus == 0) {
			isOnWay = true;
			tempCapacityBus = capacityOfBus;
		}
		else if (tempCapacityBus < 0) {
			aparts[i].numOfStudent -= (aparts[i].numOfStudent + tempCapacityBus);
			i--;
			isOnWay = true;
			tempCapacityBus = capacityOfBus;
		}
	}


	tempCapacityBus = capacityOfBus;
	isOnWay = true;
	for (int i = numOfApartment - 1; i >= pointOfSchoolOnArray; i--) {
		if (isOnWay) {
			minimumRange += 2 * (aparts[i].location - pointOfSchool);
			isOnWay = false;
		}
		tempCapacityBus -= aparts[i].numOfStudent;
		if (tempCapacityBus == 0) {
			isOnWay = true;
			tempCapacityBus = capacityOfBus;
		}
		else if (tempCapacityBus < 0) {
			aparts[i].numOfStudent -= (aparts[i].numOfStudent + tempCapacityBus);
			i++;
			isOnWay = true;
			tempCapacityBus = capacityOfBus;
		}
	}
}
int findPointsOfSchoolOnArray() {
	int tempSchoolLocation = -1; 

	for (int i = 0; i < numOfApartment; i++) {
		if (aparts[i].location > pointOfSchool) {
			tempSchoolLocation = i;
			break;
		}
	}

	if (tempSchoolLocation == -1)
		tempSchoolLocation = numOfApartment;

	return tempSchoolLocation;
}