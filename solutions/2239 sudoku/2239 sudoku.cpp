#include <iostream>
#include <cstring>
#include <cmath>
#define WIDTH 9

using namespace std;

int map[WIDTH][WIDTH];
int possibleNum[WIDTH][WIDTH][WIDTH+1];

void generatePossibleNum();
bool solveSudoku(int row, int col);
bool checkVertical(int row, int col, int value);
bool checkHorizontal(int row, int col, int value);
bool checkSquare(int row, int col, int value);

int main() {
	int input[WIDTH];
	for (int i = 0; i < WIDTH; i++)
			cin >> input[i];
	for (int i = 0; i < WIDTH; i++) {
		for (int j = WIDTH - 1; j >=0; j--) {
			map[i][j] = input[i] % 10;
			input[i] /= 10;
		}
	}
	generatePossibleNum();
	solveSudoku(0,0);

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < WIDTH; j++)
			cout << map[i][j];
		cout << endl;
	}
}

void generatePossibleNum() {
	for (int i = 0; i < WIDTH; i++) 
		for (int j = 0; j < WIDTH; j++)
			if (map[i][j] == 0) {
				for (int k = 1; k <= WIDTH; k++)
					possibleNum[i][j][k] = k;
				for (int vert = 0; vert < WIDTH; vert++)
					possibleNum[i][j][map[vert][j]] = 0;
				for (int horiz = 0; horiz < WIDTH; horiz++)
					possibleNum[i][j][map[i][horiz]] = 0;
			}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int row = i * 3, col = j * 3;
			for (int r = 0; r < 3; r++) {
				for (int c = 0; c < 3; c++) {
					for (int r2 = 0; r2 < 3; r2++)
						for (int c2 = 0; c2 < 3; c2++)
							possibleNum[row + r][col + c][map[row + r2][col + c2]] = 0;
				}
			}
		}
	}
}

bool solveSudoku(int row, int col) {
	if (map[row][col] != 0) {
		if (col < WIDTH - 1)
			return solveSudoku(row, col + 1);
		else if (row < WIDTH - 1)
			return solveSudoku(row + 1, 0);
		else
			return true;
	}
	
	for (int i = 1; i <= WIDTH; i++) {
		if (possibleNum[row][col][i] != 0 && checkVertical(row, col, i) && checkHorizontal(row, col, i) && checkSquare(row, col, i)) {
			map[row][col] = i;
			if (col < WIDTH - 1) {
				if (solveSudoku(row, col + 1))
					return true;
			}
			else if (row < WIDTH - 1) {
				if (solveSudoku(row + 1, 0))
					return true;
			}
			else
				return true;
			map[row][col] = 0;
		}
	}
	return false;
}

bool checkVertical(int row, int col, int value) {
	for (int vert = 0; vert < WIDTH; vert++) {
		if (map[vert][col] == value)
			return false;
	}
	return true;
}
bool checkHorizontal(int row, int col, int value) {
	for (int horiz = 0; horiz < WIDTH; horiz++) {
		if (map[row][horiz] == value)
			return false;
	}
	return true;
}
bool checkSquare(int row, int col, int value) {
	int sr = row / 3, sc = col / 3;
	sr *= 3;
	sc *= 3;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (map[sr + r][sc + c] == value)
				return false;
		}
	}
	return true;
}