#include <iostream>
#include <cstring>
#define MAX_TILE 10000
#define WIDTH 6
#define HEIGHT 4

using namespace std;

typedef struct Tile {
	int type;
	int row;
	int col;
} Tile;

bool blueMap[HEIGHT][WIDTH];
bool greenMap[WIDTH][HEIGHT];
int numOfTile;
Tile tile[MAX_TILE];

int getScore();
void putTile(int index);
int updateMap();
int getRestTile();

int main() {
	cin >> numOfTile;
	for (int i = 0; i < numOfTile; i++) {
		cin >> tile[i].type >> tile[i].row >> tile[i].col;
	}
	memset(blueMap, false, sizeof(blueMap));
	memset(greenMap, false, sizeof(blueMap));

	cout << getScore() << endl;
	cout << getRestTile()<<endl;
	/*
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			int temp = blueMap[i][j];
			cout << temp << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			int temp = greenMap[i][j];
			cout << temp << " ";
		}
		cout << endl;
	}
	*/
}

int getScore() {
	int score = 0;
	for (int i = 0; i < numOfTile; i++) {
		putTile(i);
		score += updateMap();
	}

	return score;
}

void putTile(int index) {
	if (tile[index].type == 1) {
		for (int i = 2; i < WIDTH; i++) {
			if (blueMap[tile[index].row][i]) {
				blueMap[tile[index].row][i-1] = true;
				break;
			}
			else if (i == WIDTH - 1)
				blueMap[tile[index].row][i] = true;
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col]) {
				greenMap[i - 1][tile[index].col] = true;
				break;
			}
			else if (i == WIDTH - 1)
				greenMap[i][tile[index].col] = true;
		}
	}
	else if (tile[index].type == 2) {	//1x2
		for (int i = 2; i < WIDTH; i++) {
			if (blueMap[tile[index].row][i]) {
				blueMap[tile[index].row][i - 1] = true;
				blueMap[tile[index].row][i - 2] = true;
				break;
			}
			else if (i == WIDTH - 1) {
				blueMap[tile[index].row][i] = true;
				blueMap[tile[index].row][i - 1] = true;
			}
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col] || greenMap[i][tile[index].col + 1]) {
				greenMap[i - 1][tile[index].col] = true;
				greenMap[i - 1][tile[index].col+1] = true;
				break;
			}
			else if (i == WIDTH - 1) {
				greenMap[i][tile[index].col] = true;
				greenMap[i][tile[index].col + 1] = true;
			}
		}
	}
	else if (tile[index].type == 3) { //2x1
		for (int i = 2; i < WIDTH; i++) {
			if (blueMap[tile[index].row][i] || blueMap[tile[index].row + 1][i]) {
				blueMap[tile[index].row][i - 1] = true;
				blueMap[tile[index].row + 1][i - 1] = true;
				break;
			}
			else if (i == WIDTH - 1) {
				blueMap[tile[index].row][i] = true;
				blueMap[tile[index].row + 1][i] = true;
			}
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col]) {
				greenMap[i - 2][tile[index].col] = true;
				greenMap[i - 1][tile[index].col] = true;
				break;
			}
			else if (i == WIDTH - 1) {
				greenMap[i][tile[index].col] = true;
				greenMap[i - 1][tile[index].col] = true;
			}
		}
		
	}
}

int updateMap() {
	//초록색은 행이 가득차면 점수 얻음
	//파랑색은 열이 가득차면 점수 얻음
	//한 행 또는 열 당 1점
	int score = 0;
	//파랑
	for (int i = 2; i < WIDTH; i++) {
		int count = 0;
		for (int j = 0; j < HEIGHT; j++) {
			if (blueMap[j][i])
				count++;
		}
		if (count == 4) {
			score++;
			bool temp[4] = { blueMap[0][0], blueMap[1][0], blueMap[2][0], blueMap[3][0] };
			for (int k = 0; k < 4; k++) blueMap[k][0] = false;
			for (int col = 1; col <= i; col++) {
				bool temp2[4] = { blueMap[0][col], blueMap[1][col], blueMap[2][col], blueMap[3][col] };
				for (int k = 0; k < 4; k++) blueMap[k][col] = temp[k];
				memcpy(temp, temp2, sizeof(temp));
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		bool check = false;
		for (int j = 0; j < HEIGHT; j++) {
			if (blueMap[j][i])
				check = true;
		}
		if (check) {
			bool temp[4] = { blueMap[0][i], blueMap[1][i], blueMap[2][i], blueMap[3][i] };
			for (int k = 0; k < 4; k++) blueMap[k][i] = false;
			for (int col = i+1; col < WIDTH; col++) {
				bool temp2[4] = { blueMap[0][col], blueMap[1][col], blueMap[2][col], blueMap[3][col] };
				for (int k = 0; k < 4; k++) blueMap[k][col] = temp[k];
				memcpy(temp, temp2, sizeof(temp));
			}
		}
	}

	//초록
	for (int i = 2; i < WIDTH; i++) {
		int count = 0;
		for (int j = 0; j < HEIGHT; j++) {
			if (greenMap[i][j])
				count++;
		}
		if (count == 4) {
			score++;
			bool temp[4] = { greenMap[0][0], greenMap[0][1], greenMap[0][2], greenMap[0][3] };
			for (int k = 0; k < 4; k++) greenMap[0][k] = false;
			for (int row = 1; row <= i; row++) {
				bool temp2[4] = { greenMap[row][0], greenMap[row][1], greenMap[row][2], greenMap[row][3] };
				for (int k = 0; k < 4; k++) greenMap[row][k] = temp[k];
				memcpy(temp, temp2, sizeof(temp));
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		bool check = false;
		for (int j = 0; j < HEIGHT; j++) {
			if (greenMap[i][j])
				check = true;
		}
		if (check) {
			bool temp[4] = { greenMap[i][0], greenMap[i][1], greenMap[i][2], greenMap[i][3] };
			for (int k = 0; k < 4; k++) greenMap[i][k] = false;
			for (int row = i+1; row < WIDTH; row++) {
				bool temp2[4] = { greenMap[row][0], greenMap[row][1], greenMap[row][2], greenMap[row][3] };
				for (int k = 0; k < 4; k++) greenMap[row][k] = temp[k];
				memcpy(temp, temp2, sizeof(temp));
			}
		}
	}

	return score;
}

int getRestTile() {
	int count = 0;
	for (int i = 0; i < 24; i++) {
		if (blueMap[i / WIDTH][i % WIDTH])
			count++;
		if (greenMap[i / HEIGHT][i % HEIGHT])
			count++;
	}
	return count;
}