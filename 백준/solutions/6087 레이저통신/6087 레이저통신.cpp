#include <iostream>
#include <list>

using namespace std;

typedef struct Location {
	int row;
	int col;
	int direction;		// 0 : 초기, 1 : 위 2 오 3 아 4 왼
	int mirror;
} Location;

int R, C;
Location start;
char map[100][100];
int visit[100][100];
int BFS();

int main() {
	cin >> C >> R;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'C') {
				start.row = i;
				start.col = j;
			}
			visit[i][j] = 2000000000;
		}
	cout << BFS();
}
int BFS() {
	list<Location> q;
	q.push_back({ start.row, start.col, 0, 0 });
	visit[start.row][start.col] = 0;
	int minMirror = 2000000000;

	while (!q.empty()) {
		int row = q.front().row, col = q.front().col, d = q.front().direction, m = q.front().mirror;
		q.pop_front();


		if ( map[row][col] == 'C') {
			minMirror = m;
		}
		if (row > 0 && map[row - 1][col] != '*' && d != 3) {
			int nextMirror = d != 4 ? d != 2 ? m : m + 1 : m + 1;
			if (nextMirror <= visit[row - 1][col]) {
				q.push_back({ row - 1, col, 1, nextMirror });
				visit[row - 1][col] = nextMirror;
			}
		}
		if (row < R - 1 && map[row + 1][col] != '*' && d != 1) {
			int nextMirror = d != 4 ? d != 2 ? m : m + 1 : m + 1;
			if (nextMirror <= visit[row + 1][col]) {
				q.push_back({ row + 1, col, 3, nextMirror });
				visit[row + 1][col] = nextMirror;
			}
		}
		if (col > 0 && map[row][col - 1] != '*' && d != 2) {
			int nextMirror = d != 3 ? d != 1 ? m : m + 1 : m + 1;
			if (nextMirror <= visit[row][col - 1]) {
				q.push_back({ row, col - 1, 4, nextMirror });
				visit[row][col - 1] = nextMirror;
			}
		}
		if (col < C - 1 && map[row][col + 1] != '*'&& d != 4) {
			int nextMirror = d != 3 ? d != 1 ? m : m + 1 : m + 1;
			if (nextMirror <= visit[row][col + 1]) {
				q.push_back({ row, col + 1, 2, nextMirror });
				visit[row][col + 1] = nextMirror;
			}
		}
	}
	return minMirror;
}