#include <iostream>
#define INF 2000000000
using namespace std;

int N, cost[1000][3], DP[1000][3];

int getMin(int deep, int bf);
int min(int a, int b) {
	return a < b ? a : b;
}
int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

	int result = INF;
	for (int i = 0; i < 3; i++) {
		result = min(result, getMin(1, i) + cost[0][i]);
	}

	cout << result;
}	

int getMin(int deep, int bf) {
	if (deep == N) {
		return 0;
	}
	if (DP[deep][bf] != 0)
		return DP[deep][bf];

	int result = INF;

	for (int i = 0; i < 3; i++)
		if (i != bf)
			result = min(result, getMin(deep + 1, i)+ cost[deep][i]);

	return DP[deep][bf] = result;
}