#include <bits/stdc++.h>

using namespace std;

struct Location {
	int row;
	int col;
	int way;	// 1~4 À§ ¿À ¾Æ ¿Þ
};

char eumap[25][25], answer;
int R, C;
Location M, Z, blank;
list<Location> q;

bool findBlank(int row, int col);		//Ã£À¸¸é true
bool goNext(Location cur);			// ºóÄ­ ¹ß°ß½Ã false. ³ª¸ÓÁö true
Location nextCell(Location c);
void fillBlank();

int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++)
		for (int j = 0; j < C; j++) {
			cin >> eumap[i][j];
			if (eumap[i][j] == 'M') 
				M = { i, j, 0 };
			else if (eumap[i][j] == 'Z') 
				Z = { i, j, 0 };
		}

	if (!findBlank(M.row, M.col))
		findBlank(Z.row, Z.col);

	fillBlank();

	cout << blank.row + 1 << " " << blank.col + 1 << " " << answer << endl;
}

bool findBlank(int r, int c) {
	if (r > 0 && eumap[r - 1][c] != '.')
		q.push_back({ r, c, 1 });
	if (c < C - 1 && eumap[r][c + 1] != '.')
		q.push_back({ r, c, 2 });
	if (r < R -1 && eumap[r + 1][c] != '.')
		q.push_back({ r, c, 3 });
	if (c > 0 && eumap[r][c - 1] != '.')
		q.push_back({ r, c, 4 });

	while (!q.empty()) {
		if (goNext(q.front()))
			q.pop_front();
		else {
			q.clear();
			return true;
		}
	}
	q.clear();
	return false;
}

bool goNext(Location cur) {
	cur = nextCell(cur);
	int r = cur.row, c = cur.col, w = cur.way;
	
	char t = eumap[r][c];

	if (t == '.') {
		blank = { r, c, w };
		return false;
	}

	if (w == 1 || w == 3) {
		if (t == '|' || t == '+')
			q.push_back({ r , c, w });
		if (t == '1' || t == '2' || t == '+')
			q.push_back({ r , c, 2 });
		if (t == '4' || t == '3' || t == '+')
			q.push_back({ r , c, 4 });
	}
	else {
		if (t == '-' || t == '+')
			q.push_back({ r, c , w });
		if (t == '3' || t == '2' || t == '+')
			q.push_back({ r, c , 1 });
		if (t == '4' || t == '1' || t == '+')
			q.push_back({ r, c , 3 });
	}
	return true;
}

Location nextCell(Location cur) {
	int r = cur.row, c = cur.col, w = cur.way;

	if (w == 1 && r > 0)
		return { r - 1, c, w };
	if (w == 2 && c < C - 1)
		return { r, c + 1, w };
	if (w == 3 && r < R - 1)
		return { r + 1, c, w };
	if (w == 4 && c > 0)
		return { r, c - 1,w};
}

void fillBlank() {
	int r = blank.row, c = blank.col, w = blank.way;
	bool check[4] = { 0,0,0,0 };
	if (r > 0) {
		char t = eumap[r - 1][c];
		check[0] = t != '|' ? t != '1' ? t != '4' ? t != '+' ? false : true : true : true : true;
	}
	if (c < C - 1) {
		char t = eumap[r][c + 1];
		check[1] = t != '-' ? t != '4' ? t != '3' ? t != '+' ? false : true : true : true : true;
	}
	if (r < R - 1) {
		char t = eumap[r + 1][c];
		check[2] = t != '|' ? t != '2' ? t != '3' ? t != '+' ? false : true : true : true : true;
	}
	if (c > 0) {
		char t = eumap[r][c-1];
		check[3] = t != '-' ? t != '2' ? t != '1' ? t != '+' ? false : true : true : true : true;
	}

	if (check[0] && check[1] && check[2] && check[3])
		answer = '+';
	else if (check[0] && check[2])
		answer = '|';
	else if (check[1] && check[3])
		answer = '-';
	else if (check[1] && check[2])
		answer = '1';
	else if (check[0] && check[1])
		answer = '2';
	else if (check[0] && check[3])
		answer = '3';
	else if (check[2] && check[3])
		answer = '4';
}