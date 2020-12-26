#include <iostream>
#include <cstring>
#define MAX_WIDTH 20
#define ASCII_A 65

using namespace std;

char map[MAX_WIDTH][MAX_WIDTH];
bool check[26];
int height, width, maxCount = 0;

void DFS(int row, int col, int deep);

int main() {
	cin >> height >> width;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			cin >> map[i][j];

	check[map[0][0] - ASCII_A] = true;
	DFS(0,0,1);
	cout << maxCount;
}

void DFS(int row, int col, int deep) {
	if (deep == 27) {
		maxCount = deep-1;
		return;
	}

	bool isEnd = true;
	if (col < width - 1 && check[map[row][col + 1] - ASCII_A] == false) {
		check[map[row][col + 1] - ASCII_A] = true;
		DFS(row, col + 1, deep + 1);
		check[map[row][col + 1] - ASCII_A] = false;
		isEnd = false;
	}
	if (row < height - 1 && check[map[row + 1][col] - ASCII_A] == false) {
		check[map[row + 1][col] - ASCII_A] = true;
		DFS(row + 1, col, deep + 1);
		check[map[row + 1][col] - ASCII_A] = false;
		isEnd = false;
	}
	if (col > 0 && check[map[row][col - 1] - ASCII_A] == false) {
		check[map[row][col - 1] - ASCII_A] = true;
		DFS(row, col - 1, deep + 1);
		check[map[row][col - 1] - ASCII_A] = false;
		isEnd = false;
	}
	if (row > 0 && check[map[row - 1][col] - ASCII_A] == false) {
		check[map[row - 1][col] - ASCII_A] = true;
		DFS(row - 1, col, deep + 1);
		check[map[row - 1][col] - ASCII_A] = false;
		isEnd = false;
	}

	if (isEnd)
		maxCount = maxCount > deep ? maxCount : deep;
}