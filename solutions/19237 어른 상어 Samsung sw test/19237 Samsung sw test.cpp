#include <iostream>
#include <cstring>
#define MAX_WIDTH 20
#define MAX_SHARK 400

using namespace std;

typedef struct Shark {
	int row;
	int col;
	int direction;		// 1: À§ 2: ¾Æ·¡ 3: ¿Þ 4: ¿À
	int way[4][4];
	bool isAlive;
} Shark;
typedef struct Smell {
	int num;
	int restTime;
} Smell;

Smell map[MAX_WIDTH][MAX_WIDTH];
Shark shark[MAX_SHARK];
int width, numOfShark, time;

int getSecondToLeaveFirstShark();
void moveShark();
bool checkShark();
void updateSmell();

int main() {
	cin >> width >> numOfShark >> time;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			int temp;
			cin >> temp;
			if (temp == 0) {
				map[i][j].num = -1;
				map[i][j].restTime = -1;
			}
			else {
				map[i][j].num = temp-1;
				map[i][j].restTime = time;
				shark[temp-1].row = i;
				shark[temp-1].col = j;
				shark[temp-1].isAlive = true;
			}
		}
	}
	for (int i = 0; i < numOfShark; i++)
		cin >> shark[i].direction;
	for (int i = 0; i < numOfShark; i++) {
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				cin >> shark[i].way[j][k];
	}

	cout << getSecondToLeaveFirstShark();
}

int getSecondToLeaveFirstShark() {
	int second = 1;
	for (; second <= 1000; second++) {
		moveShark();
		if (checkShark())
			break;
		updateSmell();
	}

	return second > 1000 ? -1 : second;
}

void moveShark() {
	int count = 0;
	int tempSharkMap[MAX_WIDTH][MAX_WIDTH];
	memset(tempSharkMap, -1, sizeof(tempSharkMap));

	for (int i = 0; i < numOfShark; i++) {
		if (!shark[i].isAlive)
			continue;

		for (int j = 0; j < 4; j++) {
			int direction = shark[i].way[shark[i].direction - 1][j];
			count++;

			if (direction == 1 && shark[i].row > 0) {
				if (map[shark[i].row - 1][shark[i].col].num == -1 || (count > 4 && map[shark[i].row - 1][shark[i].col].num == i)) {
					if (tempSharkMap[shark[i].row - 1][shark[i].col] != -1)
						shark[i].isAlive = false;
					else {
						tempSharkMap[shark[i].row - 1][shark[i].col] = i;
						shark[i].row--;
						shark[i].direction = 1;
					}
					count = 0;
					break;
				}
			}
			else if (direction == 2 && shark[i].row < (width - 1)) {
				if (map[shark[i].row + 1][shark[i].col].num == -1 || (count > 4 && map[shark[i].row + 1][shark[i].col].num == i)) {
					if (tempSharkMap[shark[i].row + 1][shark[i].col] != -1)
						shark[i].isAlive = false;
					else {
						tempSharkMap[shark[i].row + 1][shark[i].col] = i;
						shark[i].row++;
						shark[i].direction = 2;
					}
					count = 0;
					break;
				}
			}
			else if (direction == 3 && shark[i].col > 0) {
				if (map[shark[i].row][shark[i].col - 1].num == -1 || (count > 4 && map[shark[i].row][shark[i].col - 1].num == i)) {
					if (tempSharkMap[shark[i].row][shark[i].col - 1] != -1)
						shark[i].isAlive = false;
					else {
						tempSharkMap[shark[i].row][shark[i].col - 1] = i;
						shark[i].col--;
						shark[i].direction = 3;
					}
					count = 0;
					break;
				}
			}
			else if (direction == 4 && shark[i].col < (width - 1)) {
				if (map[shark[i].row][shark[i].col + 1].num == -1 || (count > 4 && map[shark[i].row][shark[i].col + 1].num == i)) {
					if (tempSharkMap[shark[i].row][shark[i].col + 1] != -1)
						shark[i].isAlive = false;
					else {
						tempSharkMap[shark[i].row][shark[i].col + 1] = i;
						shark[i].col++;
						shark[i].direction = 4;
					}
					count = 0;
					break;
				}
			}

			if (count == 4)
				i--;
			else if (count == 8) {
				if (tempSharkMap[shark[i].row][shark[i].col] != -1)
					shark[i].isAlive = false;
				else
					tempSharkMap[shark[i].row][shark[i].col] = i;
			}
		}
	}
}

bool checkShark() {
	for (int i = 1; i < numOfShark; i++) {
		if (shark[i].isAlive)
			return false;
	}
	return true;
}
void updateSmell() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			if (map[i][j].num != -1) {
				map[i][j].restTime--;
				if (map[i][j].restTime == 0) {
					map[i][j].num = -1;
					map[i][j].restTime = -1;
				}
			}
		}
	}

	for (int i = 0; i < numOfShark; i++) {
		if (shark[i].isAlive) {
			map[shark[i].row][shark[i].col].num = i;
			map[shark[i].row][shark[i].col].restTime = time;
		}
	}
}