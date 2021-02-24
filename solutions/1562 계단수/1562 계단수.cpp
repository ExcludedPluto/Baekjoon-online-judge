#include <bits/stdc++.h>
#define MAX_LENGTH 100
#define DIV 1000000000
#define ALL 1023

using namespace std;

int N, num[101];
long long DP[101][10][1 << 10];

long long getAnswer(int, int);

int main() {
	cin >> N;
	memset(DP, -1, sizeof(DP));

	long long result = 0;
	for (int i = 1; i <= 9; i++) {
		num[0] = i;
		result += getAnswer(1, 1 << i);
	}

	cout << result % DIV << endl;
}

long long getAnswer(int deep, int bit) {
	if (deep == N) {
		if (bit == ALL)
			return 1;
		return 0;
	}
	if (DP[deep][num[deep - 1]][bit] != -1)
		return DP[deep][num[deep - 1]][bit];

	long long result = 0;
	if (num[deep - 1] != 0) {
		num[deep] = num[deep - 1] - 1;
		int b = bit & (1 << num[deep]) ? bit : bit + (1 << num[deep]);
		result += getAnswer(deep + 1, b);
	}
	if (num[deep - 1] != 9) {
		num[deep] = num[deep - 1] + 1;
		int b = bit & (1 << num[deep]) ? bit : bit + (1 << num[deep]);
		result += getAnswer(deep + 1, b);
	}

	return DP[deep][num[deep-1]][bit] = result % DIV;
}
