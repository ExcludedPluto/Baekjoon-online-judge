#include <iostream>
#include <list>

using namespace std;

bool map[1000][1000];
int width, height, result = 2000000000;
int check[1000][1000];
list<pair<pair<int, int>, pair<bool, int>>> q;

int min(int a, int b) {
	return a < b ? a : b;
}
void BFS();
void push(int r, int c, bool t, int s) {
	bool temp = map[r][c] ? !t : t;
	q.push_back({ {r, c}, {temp, s} });
	check[r][c] = t ? 2 : 1;
}
bool isok(int r, int c, bool t) {
	if ((!check[r][c] || (check[r][c] == 2 && !t)) && (!map[r][c] || !t))
		return true;
	return false;
}

int main() {
	cin >> height >> width;
	for (int i = 0; i < height; i++) {
		string t;
		cin >> t;
		for (int j = 0; j < width; j++) {
			map[i][j] = t[j] - '0';
		}
	}

	BFS();
	if (result == 2000000000)
		cout << -1;
	else
		cout << result << endl;
}

void BFS() {
	q.push_back({ {0,0}, {false, 0} });
	check[0][0] = 1;

	while (!q.empty()) {
		int r = q.front().first.first, c = q.front().first.second, s = q.front().second.second;
		bool t = q.front().second.first;
		q.pop_front();
		if (r == height - 1 && c == width - 1) 
			result = min(result, s + 1);

		if (r > 0 && isok(r-1, c, t))
			push(r - 1, c, t, s + 1);
		if (r < height - 1 && isok(r+1, c, t))
			push(r + 1, c, t, s + 1);
		if (c > 0 && isok(r, c-1, t))
			push(r, c - 1, t, s + 1);
		if (c < width - 1 && isok(r, c + 1, t))
			push(r, c + 1, t, s + 1);
	}
	return;
}