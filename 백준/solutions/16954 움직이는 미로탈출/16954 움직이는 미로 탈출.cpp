#include <bits/stdc++.h>

using namespace std;

char miro[8][8];
list<pair<int, int>> q, nextq;
bool visitcheck[8][8];

bool BFS();

int main() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			cin >> miro[i][j];

	cout << BFS();
}

bool BFS() {
	bool check = false;
	nextq.push_back({ 7,0 });

	while (!nextq.empty() && !check) {
		q = nextq;
		nextq.clear();
		memset(visitcheck, 0, sizeof(visitcheck));

		while (!q.empty()) {
			int r = q.front().first, c = q.front().second;
			q.pop_front();

			if (miro[r][c] == '#')
				continue;
			if (r == 0 && c == 7) {
				check = true;
				break;
			}

			if (miro[r][c] != '#' && !visitcheck[r][c]) {
				nextq.push_back({ r, c });
				visitcheck[r][c] = true;
			}
			if (r > 0 && miro[r - 1][c] != '#' && !visitcheck[r - 1][c]) {
				nextq.push_back({ r - 1,c });
				visitcheck[r - 1][c] = true;
			}
			if (r > 0 && c < 7 && miro[r - 1][c + 1] != '#' && !visitcheck[r - 1][c + 1]) {
				nextq.push_back({ r - 1,c + 1 });
				visitcheck[r - 1][c + 1] = true;
			}
			if (c < 7 && miro[r][c + 1] != '#' && !visitcheck[r][c + 1]) {
				nextq.push_back({ r, c + 1 });
				visitcheck[r][c + 1] = true;
			}
			if (r < 7 && c < 7 && miro[r + 1][c + 1] != '#' && !visitcheck[r + 1][c + 1]) {
				nextq.push_back({ r + 1,c + 1 });
				visitcheck[r + 1][c + 1] = true;
			}
			if (r < 7 && miro[r + 1][c] != '#' && !visitcheck[r + 1][c]) {
				nextq.push_back({ r + 1,c });
				visitcheck[r + 1][c] = true;
			}
			if (r < 7 && c > 0 && miro[r + 1][c - 1] != '#' && !visitcheck[r + 1][c - 1]) {
				nextq.push_back({ r + 1,c - 1 });
				visitcheck[r + 1][c - 1] = true;
			}
			if (c > 0 && miro[r][c - 1] != '#' && !visitcheck[r][c - 1]) {
				nextq.push_back({ r, c - 1 });
				visitcheck[r][c - 1] = true;
			}
			if (r > 0 && c > 0 && miro[r - 1][c - 1] != '#' && !visitcheck[r - 1][c - 1]) {
				nextq.push_back({ r - 1,c - 1 });
				visitcheck[r - 1][c - 1] = true;
			}
		}

		for (int i = 7; i > 1; i--) 
			for (int j = 0; j < 8; j++)
				miro[i][j] = miro[i - 1][j];
		for (int j = 0; j < 8; j++)
			miro[0][j] = '.';
	}

	return check;
}