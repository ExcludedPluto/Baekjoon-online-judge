#include <iostream>
#include <cstring>
#define MAX_FILE 501

using namespace std;

int k, file[MAX_FILE], DP[MAX_FILE][MAX_FILE], fileSum[MAX_FILE][MAX_FILE], output;

int dp(int start, int end);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		cin >> k;
		for (int j = 0; j < k; j++) {
			cin >> file[j];
		}
		cout << dp(0, k - 1) << endl;
		memset(DP, 0, sizeof(DP));
		memset(fileSum, 0, sizeof(DP));
	}
}

int dp(int start, int end) {
	if (start == end)
		return 0;
	if (DP[start][end] != 0)
		return DP[start][end];

	int cur = fileSum[start][end];
	if (cur == 0) {
		for (int i = start; i <= end; i++)
			cur += file[i];
		fileSum[start][end] = cur;
	}

	int result = 2000000000;
	for (int i = start; i < end; i++) {
		result = min(result, dp(start, i) + dp(i + 1, end));
	}

	//cout << start << "\t" << end << "\t" << result << "\t" << cur <<endl;
	return DP[start][end] = result + cur;
}