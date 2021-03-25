#include <iostream>

using namespace std;

long long dp[1001][1001];

long long DP(int one, int half);

int main() {
	int N;
	while (true) {
		cin >> N;
		if (N == 0)
			break;
		cout << DP(N, 0) << endl;
	}
}

long long DP(int one, int half) {
	if (one == 0 && half == 0) 
		return 1;
	if (dp[one][half] != 0) 
		return dp[one][half];

	long long result = 0;
	if (one > 0)
		result += DP(one - 1, half + 1);
	if (half > 0)
		result += DP(one, half - 1);

	return dp[one][half] = result;
}