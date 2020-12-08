#include <iostream>
#define MAX_WIDTH 21

using namespace std;

int map[MAX_WIDTH][MAX_WIDTH];
int width;

int minDifference();
int getMin(int d1, int d2, int x, int y);

int main() {
	cin >> width;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			cin >> map[i][j];

	cout << minDifference();
}

int minDifference() {
	int minDifference = 2000000000;
	for (int d1 = 1; d1 < width - 1; d1++) {
		for (int d2 = 1; d2 < width - 1; d2++) {
			int last = width - (d1 + d2);
			for (int x = 0; x < last; x++) {
				for (int y = d1; y < (width - d2); y++) {
					int temp = getMin(d1, d2, x, y);
					if (temp < minDifference) {
						minDifference = temp;
					}
				}
			}
		}
	}

	return minDifference;
}

int getMin(int d1, int d2, int x, int y) {
	bool tempMap[MAX_WIDTH][MAX_WIDTH] = { 0, };

	int t2 = y;
	for (int t1 = x; t1 <= (x + d1); t1++) {
		tempMap[t2][t1] = true;
		t2--;
	}
	t2 = y;
	for (int t1 = x; t1 <= (x + d2); t1++) {
		tempMap[t2][t1] = true;
		t2++;
	}
	t2 = y - d1;
	for (int t1 = x + d1; t1 <= (x + d1 + d2); t1++) {
		tempMap[t2][t1] = true;
		t2++;
	}
	t2 = y + d2;
	for (int t1 = x + d2; t1 <= (x + d2 + d1); t1++) {
		tempMap[t2][t1] = true;
		t2--; 
	}

	int people[5] = { 0, };
	for (int i = 0; i < y; i++) {
		for (int j = 0; j <= (x+d1); j++) {
			if (tempMap[i][j]) {
				tempMap[i][j] = false;
				break;
			}
			people[0] += map[i][j];
			tempMap[i][j] = true;
		}
	}
	bool checkRow = true;
	for (int i = 0; i <= (y + d2 - d1); i++) {
		bool check = false;
		if (checkRow)
			check = true;
		for (int j = (x + d1 + 1); j < width; j++) {
			if (j == (x + d1 + 1) && tempMap[i][j]) {
				checkRow = false;
			}

			if (tempMap[i][j]) {
				tempMap[i][j] = false;
				check = true;
			}
			else if (check) {
				people[1] += map[i][j];
				tempMap[i][j] = true;
			}
		}
	}
	for (int i = y; i < width; i++) {
		for (int j = 0; j < (x + d2); j++) {
			if (tempMap[i][j]) {
				tempMap[i][j] = false;
				break;
			}
			people[2] += map[i][j];
			tempMap[i][j] = true;
		}
	}
	checkRow = false;
	for (int i = (y + d2 - d1 + 1); i < width; i++) {
		bool check = false;
		if (checkRow)
			check = true;
		for (int j = (x + d2); j < width; j++) {
			if (j == (x + d2) && tempMap[i][j]) {
				checkRow = true;
			}

			if (tempMap[i][j]) {
				check = true;
				tempMap[i][j] = false;
			}
			else if (check) {
				people[3] += map[i][j];
				tempMap[i][j] = true;
			}
		}
	}
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			if (!tempMap[i][j])
				people[4] += map[i][j];
		}
	}

	int minN = 200000000;
	int maxN = 0;
	for (int i = 0; i < 5; i++) {
		if (people[i] < minN)
			minN = people[i];
		if (people[i] > maxN)
			maxN = people[i];
	}
	return maxN - minN;
}