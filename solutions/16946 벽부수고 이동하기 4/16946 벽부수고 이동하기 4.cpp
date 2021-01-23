#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cstring>
#define MAX_N 1000
#define MAX_M 1000

using namespace std;

typedef struct Location {
	int row;
	int col;
} Location;

int n, m, BFSMap[MAX_N][MAX_M][2], result[MAX_N][MAX_M];
Location q[MAX_N * MAX_M];
bool map[MAX_N][MAX_M], visit[MAX_N][MAX_M];

void generateBFS();
void generateResult();
void BFS(int row, int col, int id);
int getResult(int row, int col);

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) {
			map[i][j] = s[j] - '0';
		}
	}

	generateBFS();
	generateResult();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			cout << result[i][j];
		cout << "\n";
	}
}

void generateBFS() {
	int id = 1;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			if (map[i][j] == 0 && BFSMap[i][j][0] == 0) 
				BFS(i, j, id++);
}

void BFS(int row, int col, int id) {
	int index = 0, first = 0;
	q[index++] = { row, col };
	visit[row][col] = true;

	while (first < index) {
		Location temp = q[first++];

		if (temp.row > 0 && map[temp.row - 1][temp.col] == 0 && !visit[temp.row - 1][temp.col]) {
			q[index++] = { temp.row - 1, temp.col };
			visit[temp.row - 1][temp.col] = true;
		}
		if (temp.row < n - 1 && map[temp.row + 1][temp.col] == 0 && !visit[temp.row + 1][temp.col]) {
			q[index++] = { temp.row + 1, temp.col };
			visit[temp.row + 1][temp.col] = true;
		}
		if (temp.col > 0 && map[temp.row][temp.col - 1] == 0 && !visit[temp.row][temp.col - 1]) {
			q[index++] = { temp.row, temp.col - 1 };
			visit[temp.row][temp.col - 1] = true;
		}
		if (temp.col < m - 1 && map[temp.row][temp.col + 1] == 0 && !visit[temp.row][temp.col + 1]) {
			q[index++] = { temp.row, temp.col + 1 };
			visit[temp.row][temp.col + 1] = true;
		}
	}

	for (int i = 0; i < index; i++) {
		BFSMap[q[i].row][q[i].col][0] = index;
		BFSMap[q[i].row][q[i].col][1] = id;
		visit[q[i].row][q[i].col] = false;
	}
}

void generateResult() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0)
				result[i][j] = 0;
			else
				result[i][j] = getResult(i, j) % 10;
		}
	}
}

int getResult(int row, int col) {
	int pickedId[4] = { -1, -1, -1, -1 };
	int length = 0;
	int result = 0;

	if (row > 0) {
		if (BFSMap[row - 1][col][0] != 0) {
			result += BFSMap[row - 1][col][0];
			pickedId[length++] = BFSMap[row - 1][col][1];
		}
	}
	if (row < n - 1) {
		if (BFSMap[row + 1][col][0] != 0) {
			bool check = true;
			for (int i = 0; i < length; i++) {
				if (pickedId[i] == BFSMap[row + 1][col][1])
					check = false;
			}
			if (check) {
				result += BFSMap[row + 1][col][0];
				pickedId[length++] = BFSMap[row + 1][col][1];
			}
		}
	}
	if (col > 0) {
		if (BFSMap[row][col-1][0] != 0) {
			bool check = true;
			for (int i = 0; i < length; i++) {
				if (pickedId[i] == BFSMap[row][col-1][1])
					check = false;
			}
			if (check) {
				result += BFSMap[row][col-1][0];
				pickedId[length++] = BFSMap[row][col-1][1];
			}
		}
	}
	if (col < m - 1) {
		if (BFSMap[row][col+1][0] != 0) {
			bool check = true;
			for (int i = 0; i < length; i++) {
				if (pickedId[i] == BFSMap[row][col+1][1])
					check = false;
			}
			if (check) {
				result += BFSMap[row][col+1][0];
			}
		}
	}

	return result + 1;
}