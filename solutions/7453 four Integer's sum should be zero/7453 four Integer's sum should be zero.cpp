#include <iostream>
#include <algorithm>
#define MAX_ARRAY 4000

using namespace std;

int intArray[MAX_ARRAY][4];
int firstTwo[MAX_ARRAY*MAX_ARRAY], lastTwo[MAX_ARRAY * MAX_ARRAY];
int numOfArray;

void generateSum();
long long getCount();

int main() {
	cin >> numOfArray;
	for (int i = 0; i < numOfArray; i++) {
		for (int j = 0; j < 4; j++)
			cin >> intArray[i][j];
	}

	generateSum();
	sort(firstTwo, firstTwo + numOfArray*numOfArray);
	sort(lastTwo, lastTwo + numOfArray*numOfArray);
	cout << getCount();
}

void generateSum() {
	int index = 0;
	for (int i = 0; i < numOfArray; i++) {
		for (int j = 0; j < numOfArray; j++) {
			firstTwo[index] = intArray[i][0] + intArray[j][1];
			lastTwo[index++] = intArray[i][2] + intArray[j][3];
		}
	}
}

long long getCount() {
	long long count = 0;
	int save[2] = { -1,-1 };
	for (int i = 0; i < numOfArray*numOfArray; i++) {
		int temp;
		if (save[0] == firstTwo[i]) 
			temp = save[1];
		else
			temp = (upper_bound(lastTwo, lastTwo + numOfArray * numOfArray, 0 - firstTwo[i])
				- lower_bound(lastTwo, lastTwo + numOfArray * numOfArray, 0 - firstTwo[i]));
		save[0] = firstTwo[i];
		save[1] = temp;
		count += temp;
	}
	return count;
}