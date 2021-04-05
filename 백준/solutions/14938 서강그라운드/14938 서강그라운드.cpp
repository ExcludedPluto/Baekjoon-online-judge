#include <iostream>
#include <list>
#include <cstring>
using namespace std;

int n, m, r, t, item[31], area[31][31];
int check[31];
list<pair<int, pair<int, int>>> q;

int floyd();
int max(int a, int b) {
	return a > b ? a : b;
}
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	cin >> n >> m >> r;
	for (int i = 1; i <= n; i++)
		cin >> item[i];

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (i != j)
				area[i][j] = 200000000;

	for (int i = 0; i < r; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		if (c < area[a][b]) {
			area[a][b] = c;
			area[b][a] = c;
		}
	}
	cout << floyd() << endl;
}

int floyd() {
	int result = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= n; k++) {
				if (area[j][k] > area[j][i] + area[i][k])
					area[j][k] = area[j][i] + area[i][k];
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		int temp = 0;
		for (int j = 1; j <= n; j++) {
			if (area[i][j] <= m)
				temp += item[j];
		}
		result = max(result, temp);
	}
	return result;
}

