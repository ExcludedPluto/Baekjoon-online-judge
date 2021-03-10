#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> point[100001];
int N, maxLength;
bool check[100001];

long long getLength(int cur);
long long max(long long a, long long b) {
	return a > b ? a : b;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> N;
	for (int i = 1; i <= N; i++) {
		int cur, a, b;
		cin >> cur;
		cin >> a;
		while (a != -1) {
			cin >> b;
			point[cur].push_back({ a, b });
			cin >> a;
		}
	}

	getLength(1);
	cout << maxLength;
}

long long getLength(int cur) {
	check[cur] = true;

	bool isLast = true;
	long long result[2] = { 0, 0 };
	for (int i = 0; i < point[cur].size(); i++) {
		if (!check[point[cur][i].first]) {
			long long tmp = getLength(point[cur][i].first) + point[cur][i].second;
			
			result[1] = max(result[1], tmp);
			if (result[1] > result[0]) {
				tmp = result[0];
				result[0] = result[1];
				result[1] = tmp;
			}

			isLast = false;
		}
	}

	if (isLast)
		return 0;
	else {
		maxLength =max(maxLength, result[0] + result[1]);
		return max(result[0], result[1]);
	}
}