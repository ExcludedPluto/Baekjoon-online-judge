#include <iostream>
#include <cstring>
#define MAX_WIDTH 101

using namespace std;

typedef struct Shark {
	int row;
	int col;
	int speed;
	int direction;	//1 : À§, 2 : ¾Æ·¡, 3: right, 4: left
	int size;
	bool isMoved;
	bool isAlive;
} Shark;

int map[MAX_WIDTH][MAX_WIDTH];
Shark shark[MAX_WIDTH * MAX_WIDTH];
int width, height, numOfShark;

int getSumOfSizeCaught();
Shark moveShark(Shark s);

int main() {
	cin >> height >> width >> numOfShark;
	for (int i = 0; i < height; i++)
		memset(map[i], 0, sizeof(int) * width);
	for (int i = 1; i <= numOfShark; i++) {
		cin >> shark[i].row >> shark[i].col >> shark[i].speed >> shark[i].direction >> shark[i].size;
		shark[i].row--;
		shark[i].col--;
		shark[i].isMoved = false;
		shark[i].isAlive = true;
		map[shark[i].row][shark[i].col] = i;
	}

	cout << getSumOfSizeCaught();
}

int getSumOfSizeCaught() {
	int count = 0;

	for (int col = 0; col < width; col++) {
		//catch
		for (int row = 0; row < height; row++) {
			if (map[row][col] != 0) {
				count += shark[map[row][col]].size;
				shark[map[row][col]].isAlive = false;
				map[row][col] = 0;
				break;
			}
		}

		//move and eat
		for (int i = 1; i <= numOfShark; i++) {
			if (shark[i].isAlive) {
				if (map[shark[i].row][shark[i].col] == i)
					map[shark[i].row][shark[i].col] = 0;
				//move
				shark[i] = moveShark(shark[i]);

				if (map[shark[i].row][shark[i].col] != 0 && shark[map[shark[i].row][shark[i].col]].isMoved) {
					if (shark[i].size >= shark[map[shark[i].row][shark[i].col]].size) {
						shark[map[shark[i].row][shark[i].col]].isAlive = false;
						shark[map[shark[i].row][shark[i].col]].size = 0;
						map[shark[i].row][shark[i].col] = i;
						shark[i].isMoved = true;
					}
					else {
						shark[i].isAlive = false;
						shark[i].size = 0;
					}
				}
				else {
					map[shark[i].row][shark[i].col] = i;
					shark[i].isMoved = true;
				}
			}
		}

		//init isMoved
		for (int i = 1; i <= numOfShark; i++) {
			shark[i].isMoved = false;
		}
	}

	return count;
}

Shark moveShark(Shark s) {
	int tempSpeed = s.speed;
	if (s.direction == 1) {
		if (s.speed <= s.row)
			s.row -= s.speed;
		else {
			tempSpeed -= s.row;
			int temp = (tempSpeed / (height - 1)) % 2;
			tempSpeed = tempSpeed % (height - 1);
			if (temp == 0) {
				s.row = tempSpeed;
				s.direction = 2;
			}
			else
				s.row = (height - 1) - tempSpeed;
		}
	}
	else if (s.direction == 2) {
		if (s.speed <= (height - 1) - s.row)
			s.row += s.speed;
		else {
			tempSpeed -= (height - 1) - s.row;
			int temp = (tempSpeed / (height - 1)) % 2;
			tempSpeed = tempSpeed % (height - 1);
			if (temp == 0) {
				s.row = (height - 1) - tempSpeed;
				s.direction = 1;
			}
			else
				s.row = tempSpeed;
		}
	}
	else if (s.direction == 3) {
		if (s.speed <= (width - 1) - s.col)
			s.col += s.speed;
		else {
			tempSpeed -= (width - 1) - s.col;
			int temp = (tempSpeed / (width - 1)) % 2;
			tempSpeed = tempSpeed % (width - 1);
			if (temp == 0) {
				s.col = (width - 1) - tempSpeed;
				s.direction = 4;
			}
			else
				s.col = tempSpeed;
		}
	}
	else if (s.direction == 4) {
		if (s.speed <= s.col)
			s.col -= s.speed;
		else {
			tempSpeed -= s.col;
			int temp = (tempSpeed / (width - 1)) % 2;
			tempSpeed = tempSpeed % (width - 1);
			if (temp == 0) {
				s.col = tempSpeed;
				s.direction = 3;
			}
			else
				s.col = (width - 1) - tempSpeed;
		}
	}

	return s;
}