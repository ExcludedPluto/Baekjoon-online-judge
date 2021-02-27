#include <iostream>

using namespace std;

long long map[100][100], n, m;

void flouid();

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			map[i][j] = 2000000000000;
			if (i == j)
				map[i][j] = 0;
		}

	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		map[a-1][b-1] = c < map[a-1][b-1] ? c : map[a - 1][b - 1];
	}

	flouid();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			long long t = map[i][j] == 2000000000000 ? 0 : map[i][j];
			cout << t << " ";
		}
		cout << endl;
	}

}

void flouid() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				map[j][k] = map[j][k] < (map[j][i] + map[i][k]) ? map[j][k] : (map[j][i] + map[i][k]);
			}
		}
	}
}