#include <iostream>
#include <cstring>
#define MAX_WIDTH 21
#define MAX_DEEP 5

using namespace std;

int map[MAX_WIDTH][MAX_WIDTH];
int maxCell = 0;
int width;

void getProperties();
void moveDP(int (*currentMap)[MAX_WIDTH], int deep = 0);
void test() {
	int m[3][3] = { 1,2,3,4,5,6,7,8,9 };
	int(*map)[3] = m;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << map[i][j];
		cout << endl;
	}
	cout << endl;
	int temp[3][3];
	for (int i = 0; i < 3; i++)
		memcpy(temp[i], map[i], sizeof(int) * 3);

	temp[0][0] = 0;
	temp[1][1] = 0;
	temp[2][2] = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << map[i][j];
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << temp[i][j];
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 3; i++)
		memcpy(temp[i], map[i], sizeof(int) * 3);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << temp[i][j];
		cout << endl;
	}
	cout << endl;

	temp[0][0] = 0;
	temp[1][1] = 0;
	temp[2][2] = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << temp[i][j];
		cout << endl;
	}
	cout << endl;
}
int main() {
	//test();
	while (true) {
		getProperties();
		moveDP(map);
		cout << maxCell;
		maxCell = 0;
	}
}

void getProperties() {
	cin >> width;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			cin >> map[i][j];
}

/*
10
8  8 4 16 32 0 0 8 8 8
8  8 4 0  0  8 0 0 0 0
16 0 0 16 0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 0
0  0 0 0  0  0 0 0 0 16
0  0 0 0  0  0 0 0 0 2
위 오오위오 -> 128
*/
void moveDP(int(*currentMap)[MAX_WIDTH], int deep) {
	if (deep == MAX_DEEP) {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < width; j++) {
				if (currentMap[i][j] > maxCell)
					maxCell = currentMap[i][j];
				//cout << currentMap[i][j];
			}
			//cout << endl;
		}
		//cout << endl;
		return;
	}
	int tempMap[MAX_WIDTH][MAX_WIDTH];
	bool updated[MAX_WIDTH][MAX_WIDTH] = { 0, };
	for (int i = 0; i < MAX_WIDTH; i++)
		memcpy(tempMap[i], currentMap[i], sizeof(int) * MAX_WIDTH);

	//위
	for (int row = 1; row < width; row++)
		for (int col = 0; col < width; col++)
			if (tempMap[row][col] != 0) 
				for (int m = row - 1; m >= 0; m--) {
					if (tempMap[m][col] != 0) {
						if (tempMap[m][col] == tempMap[row][col] && !updated[m][col]) {
							tempMap[m][col] *= 2;
							tempMap[row][col] = 0;
							updated[m][col] = true;
						}
						else {
							tempMap[m + 1][col] = tempMap[row][col];
							tempMap[row][col] = m == (row -1) ? tempMap[row][col] : 0;
						}
						break;
					}
					else if (m == 0) {
						tempMap[m][col] = tempMap[row][col];
						tempMap[row][col] = 0;
					}
				}
	moveDP(tempMap, deep + 1);
	for (int i = 0; i < MAX_WIDTH; i++) {
		memcpy(tempMap[i], currentMap[i], sizeof(int) * MAX_WIDTH);
		memset(updated[i], 0, sizeof(bool) * MAX_WIDTH);
	}

	//오른쪽
	for (int col = width-2; col >= 0; col--)
		for (int row = 0; row < width; row++)
			if (tempMap[row][col] != 0)
				for (int m = col + 1; m <= width-1; m++) {
					if (tempMap[row][m] != 0) {
						if (tempMap[row][m] == tempMap[row][col] && !updated[row][m]) {
							tempMap[row][m] *= 2;
							tempMap[row][col] = 0;
							updated[row][m] = true;
						}
						else {
							tempMap[row][m-1] = tempMap[row][col];
							tempMap[row][col] = m == (col + 1) ? tempMap[row][col] : 0;
						}
						break;
					}
					else if (m == width-1) {
						tempMap[row][m] = tempMap[row][col];
						tempMap[row][col] = 0;
					}
				}
	moveDP(tempMap, deep + 1);
	for (int i = 0; i < MAX_WIDTH; i++) {
		memcpy(tempMap[i], currentMap[i], sizeof(int) * MAX_WIDTH);
		memset(updated[i], 0, sizeof(bool) * MAX_WIDTH);
	}

	//아래
	for (int row = width-2; row >= 0; row--)
		for (int col = 0; col < width; col++)
			if (tempMap[row][col] != 0)
				for (int m = row + 1; m <= width-1; m++) {
					if (tempMap[m][col] != 0) {
						if (tempMap[m][col] == tempMap[row][col] && !updated[m][col]) {
							tempMap[m][col] *= 2;
							tempMap[row][col] = 0;
							updated[m][col] = true;
						}
						else {
							tempMap[m - 1][col] = tempMap[row][col];
							tempMap[row][col] = m == (row + 1) ? tempMap[row][col] : 0;
						}
						break;
					}
					else if (m == width-1) {
						tempMap[m][col] = tempMap[row][col];
						tempMap[row][col] = 0;
					}
				}
	moveDP(tempMap, deep + 1);
	for (int i = 0; i < MAX_WIDTH; i++) {
		memcpy(tempMap[i], currentMap[i], sizeof(int) * MAX_WIDTH);
		memset(updated[i], 0, sizeof(bool) * MAX_WIDTH);
	}

	//왼쪽
	for (int col = 1; col <= width-1; col++)
		for (int row = 0; row < width; row++)
			if (tempMap[row][col] != 0)
				for (int m = col - 1; m >= 0; m--) {
					if (tempMap[row][m] != 0) {
						if (tempMap[row][m] == tempMap[row][col] && !updated[row][m]) {
							tempMap[row][m] *= 2;
							tempMap[row][col] = 0;
							updated[row][m] = true;
						}
						else {
							tempMap[row][m + 1] = tempMap[row][col];
							tempMap[row][col] = m == (col - 1) ? tempMap[row][col] : 0;
						}
						break;
					}
					else if (m == 0) {
						tempMap[row][m] = tempMap[row][col];
						tempMap[row][col] = 0;
					}
				}
	moveDP(tempMap, deep + 1);
	for (int i = 0; i < MAX_WIDTH; i++) {
		memcpy(tempMap[i], currentMap[i], sizeof(int) * MAX_WIDTH);
		memset(updated[i], 0, sizeof(bool) * MAX_WIDTH);
	}
}