#include <iostream>
#include <vector>
#include <list>
#define MAX_WIDTH 1500

using namespace std;

typedef struct Location {
	int row;
	int col;
} Location;

int row, col, todayLength;
Location bird1, bird2;
Location meltToday[MAX_WIDTH*MAX_WIDTH];
char map[MAX_WIDTH][MAX_WIDTH];
bool visit[MAX_WIDTH][MAX_WIDTH], meltVisit[MAX_WIDTH][MAX_WIDTH];
list<Location> q;

bool init();
void initBird(Location bird, char c);
bool meltIce();
bool checkBird(int r, int c);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> row >> col;

	bool check = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'L') {
				if (!check) {
					bird1.row = i;
					bird1.col = j;
					check = true;
				}
				else {
					bird2.row = i;
					bird2.col = j;
					map[i][j] = 'l';
				}
			}
		}
	}

	if (init()) {
		cout << 0;
		return 0;
	}

	int day = 1;
	while (true) {
		cout << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				cout << map[i][j];
			cout << endl;
		}
		cout << endl;
		if (meltIce()) {
			cout << day;
			break;
		}
		day++;
	}
}

bool init() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == 'X') {
				if (i > 0 && map[i - 1][j] != 'X') {
					meltToday[todayLength++] = { i, j };
					meltVisit[i][j] = true;
				}
				else if (j < col - 1 && map[i][j + 1] != 'X') {
					meltToday[todayLength++] = { i, j };
					meltVisit[i][j] = true;
				}
				else if (i < row - 1 && map[i + 1][j] != 'X') {
					meltToday[todayLength++] = { i, j };
					meltVisit[i][j] = true;
				}
				else if (j > 0 && map[i][j - 1] != 'X') {
					meltToday[todayLength++] = { i, j };
					meltVisit[i][j] = true;
				}
			}
		}
	}

	initBird(bird1, 'L');
	if (map[bird2.row][bird2.col] == 'L')
		return true;
	initBird(bird2, 'l');
	return false;
}

void initBird(Location bird, char c) {
	q.push_back({ bird.row, bird.col });
	visit[bird.row][bird.col] = true;

	while (!q.empty()) {
		Location temp = q.front();
		q.pop_front();
		map[temp.row][temp.col] = c;

		if (temp.row > 0 && !visit[temp.row - 1][temp.col] && map[temp.row - 1][temp.col] != 'X') {
			q.push_back({ temp.row - 1, temp.col });
			visit[temp.row - 1][temp.col] = true;
		}
		if (temp.row < row - 1 && !visit[temp.row + 1][temp.col] && map[temp.row + 1][temp.col] != 'X') {
			q.push_back({ temp.row + 1, temp.col });
			visit[temp.row + 1][temp.col] = true;
		}
		if (temp.col > 0 && !visit[temp.row][temp.col - 1] && map[temp.row][temp.col - 1] != 'X') {
			q.push_back({ temp.row, temp.col -1 });
			visit[temp.row][temp.col - 1] = true;
		}
		if (temp.col < col - 1 && !visit[temp.row][temp.col + 1] && map[temp.row][temp.col + 1] != 'X') {
			q.push_back({ temp.row, temp.col + 1});
			visit[temp.row][temp.col + 1] = true;
		}
	}
}

bool meltIce() {
	int index = 0;
	vector<Location> q;

	while (index < todayLength) {
		if (checkBird(meltToday[index].row, meltToday[index].col))
			return true;

		if (meltToday[index].row > 0 && map[meltToday[index].row - 1][meltToday[index].col] == 'X' && !meltVisit[meltToday[index].row-1][meltToday[index].col] ) {
			q.push_back({ meltToday[index].row - 1, meltToday[index].col });
			meltVisit[meltToday[index].row - 1][meltToday[index].col] = true;
		}

		if (meltToday[index].col < col - 1 && map[meltToday[index].row][meltToday[index].col + 1] == 'X' && !meltVisit[meltToday[index].row][meltToday[index].col + 1]) {
			q.push_back({ meltToday[index].row, meltToday[index].col + 1 });
			meltVisit[meltToday[index].row][meltToday[index].col + 1] = true;
		}

		if (meltToday[index].row < row - 1 && map[meltToday[index].row + 1][meltToday[index].col] == 'X' && !meltVisit[meltToday[index].row + 1][meltToday[index].col]) {
			q.push_back({ meltToday[index].row + 1, meltToday[index].col });
			meltVisit[meltToday[index].row + 1][meltToday[index].col] = true;
		}

		if (meltToday[index].col > 0 && map[meltToday[index].row][meltToday[index].col - 1] == 'X' && !meltVisit[meltToday[index].row][meltToday[index].col - 1]) {
			q.push_back({ meltToday[index].row, meltToday[index].col - 1 });
			meltVisit[meltToday[index].row][meltToday[index].col - 1] = true;
		}

		index++;
	}
	todayLength = 0;

	//³Ö±â
	for (int i = 0; i < q.size(); i++) 
		meltToday[todayLength++] = q[i];

	return false;
}

bool checkBird(int r, int c) {
	bool checkL = false, checkl = false;
	if (r > 0 && map[r - 1][c] == 'L')
		checkL = true;
	else if (r < row - 1 && map[r + 1][c] == 'L')
		checkL = true;
	else if (c > 0 && map[r][c - 1] == 'L')
		checkL = true;
	else if (c < col - 1 && map[r][c + 1] == 'L')
		checkL = true;

	if (r > 0 && map[r - 1][c] == 'l')
		checkl = true;
	else if (r < row - 1 && map[r + 1][c] == 'l')
		checkl = true;
	else if (c > 0 && map[r][c - 1] == 'l')
		checkl = true;
	else if (c < col - 1 && map[r][c + 1] == 'l')
		checkl = true;

	if (checkL && checkl)
		return true;
	else if (checkL) {
		map[r][c] = 'L';
		initBird({ r,c }, 'L');
		if (map[bird2.row][bird2.col] == 'L')
			return true;
	}
	else if (checkl) {
		map[r][c] = 'l';
		initBird({ r,c }, 'l');
		if (map[bird1.row][bird1.col] == 'l')
			return true;
	}
	else
		map[r][c] = '.';
	return false;
}