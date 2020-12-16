#include <iostream>
#include <cstring>
#include <vector>
#define MAX_WIDTH 13

using namespace std;

typedef struct Piece {
	int row;
	int col;
	int direction; // 1: ¿À 2 : ¿Þ 3 : À§ 4 : ¾Æ
} Piece;

Piece piece[11];
int map[MAX_WIDTH][MAX_WIDTH];
int pieceMap[MAX_WIDTH][MAX_WIDTH][4];
int indexMap[MAX_WIDTH][MAX_WIDTH];
int width, numOfPiece;

int getLastTurnNum();

int main() {
	cin >> width >> numOfPiece;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			cin >> map[i][j];
		}
	}
	memset(pieceMap, -1, sizeof(pieceMap));
	memset(indexMap, 0, sizeof(indexMap));
	for (int i = 0; i < numOfPiece; i++) {
		cin >> piece[i].row >> piece[i].col >> piece[i].direction;
		piece[i].row--;
		piece[i].col--;
		pieceMap[piece[i].row][piece[i].col][indexMap[piece[i].row][piece[i].col]++] = i;
	}

	cout << getLastTurnNum();
}

int getLastTurnNum() {
	for (int turn = 1; turn <= 1000; turn++) {
		int temp[10];
		memset(temp, 0, sizeof(temp));

		for (int i = 0; i < numOfPiece; i++) {
			if (temp[i] >= 2)
				continue;
			else
				temp[i]++;

			int row = piece[i].row;
			int col = piece[i].col;
			int stackIndex = 0;
			int lastIndex = indexMap[row][col];
			for (stackIndex; stackIndex < lastIndex; stackIndex++)
				if (pieceMap[row][col][stackIndex] == i)
					break;

			if (piece[i].direction == 1) {
				if (col >= (width - 1) || map[row][col + 1] == 2) {
					if(temp[i] != 2)
						piece[i].direction = 2;
					i--;
				}
				else if (map[row][col + 1] == 1) {
					for (int j = lastIndex - 1; j >= stackIndex; j--) {
						pieceMap[row][col + 1][indexMap[row][col + 1]++] = pieceMap[row][col][j];
						if (indexMap[row][col + 1] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].col++;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
				else if (map[row][col + 1] == 0) {
					for (int j = stackIndex; j < lastIndex; j++) {
						pieceMap[row][col + 1][indexMap[row][col + 1]++] = pieceMap[row][col][j];
						if (indexMap[row][col + 1] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].col++;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
			}
			else if (piece[i].direction == 2) {
				if (col <= 0 || map[row][col - 1] == 2) {
					if (temp[i] != 2)
						piece[i].direction = 1;
					i--;
				}
				else if (map[row][col - 1] == 1) {
					for (int j = lastIndex - 1; j >= stackIndex; j--) {
						pieceMap[row][col - 1][indexMap[row][col - 1]++] = pieceMap[row][col][j];
						if (indexMap[row][col - 1] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].col--;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
				else if (map[row][col - 1] == 0) {
					for (int j = stackIndex; j < lastIndex; j++) {
						pieceMap[row][col - 1][indexMap[row][col - 1]++] = pieceMap[row][col][j];
						if (indexMap[row][col - 1] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].col--;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
			}
			else if (piece[i].direction == 3) {
				if (row <= 0 || map[row-1][col] == 2) {
					if (temp[i] != 2)
						piece[i].direction = 4;
					i--;
				}
				else if (map[row-1][col] == 1) {
					for (int j = lastIndex - 1; j >= stackIndex; j--) {
						pieceMap[row-1][col][indexMap[row-1][col]++] = pieceMap[row][col][j];
						if (indexMap[row-1][col] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].row--;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
				else if (map[row-1][col] == 0) {
					for (int j = stackIndex; j < lastIndex; j++) {
						pieceMap[row - 1][col][indexMap[row - 1][col]++] = pieceMap[row][col][j];
						if (indexMap[row - 1][col] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].row--;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
			}
			else if(piece[i].direction == 4) {
				if (row >= (width - 1) || map[row+1][col] == 2) {
					if (temp[i] != 2)
						piece[i].direction = 3;
					i--;
				}
				else if (map[row+1][col] == 1) {
					for (int j = lastIndex - 1; j >= stackIndex; j--) {
						pieceMap[row + 1][col][indexMap[row + 1][col]++] = pieceMap[row][col][j];
						if (indexMap[row + 1][col] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].row++;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
				else if (map[row+1][col] == 0) {
					for (int j = stackIndex; j < lastIndex; j++) {
						pieceMap[row + 1][col][indexMap[row + 1][col]++] = pieceMap[row][col][j];
						if (indexMap[row + 1][col] >= 4)
							return turn;
						piece[pieceMap[row][col][j]].row++;
						pieceMap[row][col][j] = -1;
						indexMap[row][col]--;
					}
				}
			}
		}
	}

	return -1;
}