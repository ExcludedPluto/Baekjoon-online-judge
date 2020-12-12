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

int blueMap[HEIGHT][WIDTH];
int greenMap[WIDTH][HEIGHT];
int numOfTile;
Tile tile[MAX_TILE];

int getScore();
void putTile(int index);
void putTile(int row, int col, int map);
int updateMap();
int getRestTile();

int main() {
	cin >> numOfTile;
	for (int i = 0; i < numOfTile; i++) {
		cin >> tile[i].type >> tile[i].row >> tile[i].col;
	}
	memset(blueMap, 0, sizeof(blueMap));
	memset(greenMap, 0, sizeof(blueMap));

	cout << getScore() << endl;
	cout << getRestTile() << endl;
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
			if (blueMap[tile[index].row][i] != 0) {
				blueMap[tile[index].row][i - 1] = index+1;
				break;
			}
			else if (i == WIDTH - 1)
				blueMap[tile[index].row][i] = index+1;
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col] != 0) {
				greenMap[i - 1][tile[index].col] = index+1;
				break;
			}
			else if (i == WIDTH - 1)
				greenMap[i][tile[index].col] = index+1;
		}
	}
	else if (tile[index].type == 2) {	//1x2
		for (int i = 2; i < WIDTH; i++) {
			if (blueMap[tile[index].row][i] != 0) {
				blueMap[tile[index].row][i - 1] = index+1;
				blueMap[tile[index].row][i - 2] = index+1;
				break;
			}
			else if (i == WIDTH - 1) {
				blueMap[tile[index].row][i] = index+1;
				blueMap[tile[index].row][i - 1] = index+1;
			}
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col] != 0|| greenMap[i][tile[index].col + 1] != 0) {
				greenMap[i - 1][tile[index].col] = index+1;
				greenMap[i - 1][tile[index].col + 1] = index+1;
				break;
			}
			else if (i == WIDTH - 1) {
				greenMap[i][tile[index].col] = index+1;
				greenMap[i][tile[index].col + 1] = index+1;
			}
		}
	}
	else if (tile[index].type == 3) { //2x1
		for (int i = 2; i < WIDTH; i++) {
			if (blueMap[tile[index].row][i] != 0 || blueMap[tile[index].row + 1][i] != 0) {
				blueMap[tile[index].row][i - 1] = index+1;
				blueMap[tile[index].row + 1][i - 1] = index+1;
				break;
			}
			else if (i == WIDTH - 1) {
				blueMap[tile[index].row][i] = index+1;
				blueMap[tile[index].row + 1][i] = index+1;
			}
		}

		for (int i = 2; i < WIDTH; i++) {
			if (greenMap[i][tile[index].col] != 0) {
				greenMap[i - 2][tile[index].col] = index+1;
				greenMap[i - 1][tile[index].col] = index+1;
				break;
			}
			else if (i == WIDTH - 1) {
				greenMap[i][tile[index].col] = index+1;
				greenMap[i - 1][tile[index].col] = index+1;
			}
		}

	}
}

void putTile(int row, int col, int map) {
	if (map == 0) {
		int temp = blueMap[row][col];
		blueMap[row][col] = 0;
		blueMap[row + 1][col] = 0;
		for (int i = col + 1; i < WIDTH; i++) {
			if (blueMap[row][i] != 0 || blueMap[row + 1][i] != 0) {
				blueMap[row][i - 1] = temp;
				blueMap[row + 1][i - 1] = temp;
				break;
			}
			else if (i == WIDTH - 1) {
				blueMap[row][i] = temp;
				blueMap[row + 1][i] = temp;
			}
		}
	}
	else if (map == 1) {
		int temp = greenMap[row][col];
		greenMap[row][col] = 0;
		greenMap[row][col + 1] = 0;
		for (int i = row + 1; i < WIDTH; i++) {
			if (greenMap[i][col] != 0 || greenMap[i][col + 1] != 0) {
				greenMap[i - 1][col] = temp;
				greenMap[i - 1][col + 1] = temp;
				break;
			}
			else if (i == WIDTH - 1) {
				greenMap[i][col] = temp;
				greenMap[i][col + 1] = temp;
			}
		}

	}
}

int updateMap() {
	int score = 0;
	//파랑
	for (int i = 2; i < WIDTH; i++) {
		int count = 0;
		for (int j = 0; j < HEIGHT; j++) {
			if (blueMap[j][i] != 0)
				count++;
		}
		if (count == 4) {
			score++;
			for (int k = 0; k < 4; k++) blueMap[k][i] = 0;
			//2*1 일때만 따로 처리해주면 됨
			for (int j = i-1; j >=0; j--) {
				for (int k = 0; k <= HEIGHT; k++) {
					if (blueMap[k][j] != 0) {
						if (k != HEIGHT - 1 && blueMap[k + 1][j] == blueMap[k][j])
							putTile(k, j, 0);
						else {
							int temp = blueMap[k][j];
							blueMap[k][j] = 0;
							for (int tempCol = j + 1; tempCol < WIDTH; tempCol++) {
								if (blueMap[k][tempCol] != 0) {
									blueMap[k][tempCol - 1] = temp;
									break;
								}
								else if (tempCol == WIDTH - 1)
									blueMap[k][tempCol] = temp;
							}
						}
					}
				}
			}
			i = 2;
		}
	}
	for (int i = 0; i < 2; i++) {
		bool check = false;
		for (int j = 0; j < HEIGHT; j++) {
			if (blueMap[j][i])
				check = true;
		}
		if (check) {
			int temp[4] = { blueMap[0][i], blueMap[1][i], blueMap[2][i], blueMap[3][i] };
			for (int k = 0; k < 4; k++) blueMap[k][i] = 0;
			for (int col = i + 1; col < WIDTH; col++) {
				int temp2[4] = { blueMap[0][col], blueMap[1][col], blueMap[2][col], blueMap[3][col] };
				for (int k = 0; k < 4; k++) blueMap[k][col] = temp[k];
				memcpy(temp, temp2, sizeof(temp));
			}
		}
	}

	//초록
	for (int i = 2; i < WIDTH; i++) {
		int count = 0;
		for (int j = 0; j < HEIGHT; j++) {
			if (greenMap[i][j] != 0)
				count++;
		}
		if (count == 4) {
			score++;
			for (int k = 0; k < 4; k++) greenMap[i][k] = 0;
			for (int j = i-1; j >= 0; j--) {
				for (int k = 0; k < HEIGHT; k++) {
					if (greenMap[j][k] != 0) {
						if (k != HEIGHT - 1 && greenMap[j][k] == greenMap[j][k + 1]) {//옯기고, 다음 k에서 출동?
							putTile(j, k, 1);
						}
						else {
							int temp = greenMap[j][k];
							greenMap[j][k] = 0;
							for (int tempRow = j + 1; tempRow < WIDTH; tempRow++) {
								if (greenMap[tempRow][k] != 0) {
									greenMap[tempRow - 1][k] = temp;
									break;
								}
								else if (tempRow == WIDTH - 1)
									greenMap[tempRow][k] = temp;
							}
						}
					}
				}
			}
			i = 2;
		}
	}
	for (int i = 0; i < 2; i++) {
		bool check = false;
		for (int j = 0; j < HEIGHT; j++) {
			if (greenMap[i][j])
				check = true;
		}
		if (check) {
			int temp[4] = { greenMap[i][0], greenMap[i][1], greenMap[i][2], greenMap[i][3] };
			for (int k = 0; k < 4; k++) greenMap[i][k] = 0;
			for (int row = i + 1; row < WIDTH; row++) {
				int temp2[4] = { greenMap[row][0], greenMap[row][1], greenMap[row][2], greenMap[row][3] };
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
		if (blueMap[i / WIDTH][i % WIDTH] != 0)
			count++;
		if (greenMap[i / HEIGHT][i % HEIGHT] != 0)
			count++;
	}
	return count;
}