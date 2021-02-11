#include <iostream>
#include <cstring>
#define MAX_WIDTH 20

using namespace std;

typedef struct Location {
	int row;
	int col;
	int length;
} Location;

int w, h, numOfD = 1, eachOther[11][11];
char map[MAX_WIDTH][MAX_WIDTH];
Location q[MAX_WIDTH * MAX_WIDTH], node[11];
bool visit[MAX_WIDTH][MAX_WIDTH], visitDistance[11];

void BFS(Location s);
int minDistance(int d, int cur);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	while (true) {
		cin >> w >> h;
		if (w == 0 && h == 0)
			break;

		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++) {
				cin >> map[i][j];
				if (map[i][j] == 'o') {
					map[i][j] = '0';			// start는 0, 더티는 1~10
					node[0] = { i, j };
				}
				else if (map[i][j] == '*') {
					node[numOfD] = { i, j };
					map[i][j] = '0' + numOfD++;
				}
			}

		for (int i = 0; i < numOfD; i++)
			BFS(node[i]);

		int count = 0;
		for (int i = 1; i < numOfD; i++)
			if (eachOther[0][i] > 0)
				count++;

		if (count < numOfD - 1) 
			cout << -1 << endl;
		else
			cout << minDistance(0, 0) << endl;

		numOfD = 1;
		memset(eachOther, 0, sizeof(eachOther));
	}
}

void BFS(Location s) {
	//start면 0, 더러운 곳이면 1~10 들어감
	int cur = map[s.row][s.col] - '0';

	int length = 0, index = 0;
	q[length++] = { s.row, s.col, 0 };
	visit[s.row][s.col] = true;

	while (index < length) {
		int row = q[index].row, col = q[index].col, l = q[index++].length;

		if (map[row][col] - '0' >= 1 && map[row][col] - '0' <= 10) {
			eachOther[cur][map[row][col] - '0'] = l;
		}

		if (row > 0 && !visit[row - 1][col] && map[row - 1][col] != 'x') {
			q[length++] = { row - 1,col, l + 1 };
			visit[row - 1][col] = true;
		}
		if (row < h - 1 && !visit[row + 1][col] && map[row + 1][col] != 'x') {
			q[length++] = { row + 1,col, l + 1 };
			visit[row + 1][col] = true;
		}
		if (col > 0 && !visit[row][col - 1] && map[row][col - 1] != 'x') {
			q[length++] = { row,col - 1, l + 1 };
			visit[row][col - 1] = true;
		}
		if (col < w - 1 && !visit[row][col + 1] && map[row][col + 1] != 'x') {
			q[length++] = { row, col + 1, l + 1 };
			visit[row][col + 1] = true;
		}
	}
	for (int i = 0; i < length; i++)
		visit[q[i].row][q[i].col] = false;
}

int minDistance(int d, int cur) {
	int result = 2000000000;
	bool check = true;

	for (int i = 1; i < numOfD; i++) {
		if (!visitDistance[i]) {
			visitDistance[i] = true;
			result = min(result, minDistance(d + eachOther[cur][i], i));
			visitDistance[i] = false;
			check = false;
		}
	}

	if (check)
		return d;
	else
		return result;
}