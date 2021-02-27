#include <bits/stdc++.h>

using namespace std;

char house[50][50];
int DP[50][50];
list<pair<pair<int, int>, pair<int, int>>> q;
int N, r, c;

int BFS();
void nextRC(int* row, int* col, int way);

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> house[i][j];
			if (house[i][j] == '#') {
				r = i;
				c = j;
			}
			DP[i][j] = 2000000000;
		}
	
	cout << BFS();
}


int BFS() {
	int result = 2000000000;
	
	if(r > 0 && house[r-1][c] != '*')
		q.push_back({ {r, c}, {1, 0} });
	if (r < N - 1 && house[r + 1][c] != '*')
		q.push_back({ {r, c}, {3, 0} });
	if (c < N - 1 && house[r][c + 1] != '*')
		q.push_back({ {r, c}, {2, 0} });
	if (c > 0 && house[r][c - 1] != '*')
		q.push_back({ {r, c}, {4, 0} });

	while (!q.empty()) {
		int row = q.front().first.first, col = q.front().first.second, w = q.front().second.first, n = q.front().second.second;
		q.pop_front();

		if (house[row][col] == '#' && !(row == r && col == c)) {
			result = result < n ? result : n;
			continue;
		}

		nextRC(&row, &col, w);

		//위로 갈수도, 느낌표일경우 좌우 가능

		if ((row >= 0 && row <= N - 1) && (col >= 0 && col <= N - 1) && house[row][col] != '*') {
			q.push_back({ {row, col}, {w, n} });
			if (house[row][col] == '!' && n + 1 < DP[row][col]) {
				DP[row][col] = n + 1;
				if (w == 1 || w == 3) {
					q.push_back({ {row, col}, {2, n + 1} });
					q.push_back({ {row, col}, {4, n + 1} });
				}
				else {
					q.push_back({ { row, col }, { 1, n + 1 } });
					q.push_back({ { row, col }, { 3, n + 1 } });
				}
			}
		}
	}
	return result;
}

void nextRC(int* row, int* col, int way) {
	if (way == 1)
		*row = (*row) - 1;
	else if (way == 2)
		*col = (*col) + 1;
	else if (way == 3)
		*row = (*row) + 1;
	else if (way == 4)
		*col = (*col) - 1;
}