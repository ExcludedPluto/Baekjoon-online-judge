#include <iostream>
#include <cstring>
#include <list>

using namespace std;

int N, K, result = 2000000000;
int check[200020];
list<pair<int,int>> q;

int bfs();
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	for (int i = 0; i < 200020; i++)
		check[i] = 2000000000;

	cin >> N >> K;
	if (N >= K)
		cout << N - K;
	else
		cout << bfs() << endl;

}

int bfs() {
	q.push_back({ N, 0 });
	check[N] = 0;

	while (!q.empty()) {
		int X = q.front().first, t = q.front().second;
		q.pop_front();

		if (X >= K) {
			result = min(result, X - K + t);
		}
		else {
			if (X != 0 && t < check[X * 2]) {
				q.push_back({ X * 2, t });
				check[X * 2] = t;
			}
			if (t + 1 < check[X + 1]) {
				q.push_back({ X + 1, t + 1 });
				check[X + 1] = t + 1;
			}
			if (X-1 >= 0 && t + 1 < check[X - 1]) {
				q.push_back({ X - 1, t + 1 });
				check[X - 1] = t + 1;
			}
		}
	}
	return result;
}