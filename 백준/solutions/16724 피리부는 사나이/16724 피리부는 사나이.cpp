#include <iostream>
#include <vector>
#include <string>
#define MAX_WIDTH 1000

using namespace std;

typedef struct Location {
	int row;
	int col;

} Location;

char map[MAX_WIDTH][MAX_WIDTH];
int n, m, safezone;
bool visit[MAX_WIDTH][MAX_WIDTH], tempVisit[MAX_WIDTH][MAX_WIDTH];

void generateSafezone();
bool DFS(int row, int col);
Location getNextCell(Location cur);

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string temp;
		cin >> temp;
		for (int j = 0; j < m; j++) {
			map[i][j] = temp[j];
		}
	}
	generateSafezone();
	cout << safezone;
}


void generateSafezone() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (!visit[i][j]) {
				if (DFS(i, j)) {
					safezone++;
				}
			}
}

bool DFS(int row, int col) {
	vector<Location> q;
	Location cur = { row,col };

	while (!visit[cur.row][cur.col] && !tempVisit[cur.row][cur.col]) {
		q.push_back({ cur.row, cur.col });
		tempVisit[cur.row][cur.col] = true;
		cur = getNextCell(cur);
	}

	bool result;
	if (visit[cur.row][cur.col])
		result = false;
	else
		result =  true;

	for (int i = 0; i < q.size(); i++) {
		visit[q[i].row][q[i].col] = true;
		tempVisit[q[i].row][q[i].col] = false;
	}
	return result;
}

Location getNextCell(Location cur) {
	if (map[cur.row][cur.col] == 'D') 
		return { cur.row + 1, cur.col };
	else if (map[cur.row][cur.col] == 'U') 
		return { cur.row - 1, cur.col };
	else if (map[cur.row][cur.col] == 'L') 
		return { cur.row, cur.col - 1 };
	else 
		return { cur.row, cur.col + 1 };
}