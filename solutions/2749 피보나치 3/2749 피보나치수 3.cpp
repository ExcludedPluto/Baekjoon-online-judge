#include <iostream>
#define MOD 1000000
using namespace std;

int	DP[1500000] = { 0, 1, }, i = 2;

int main() {
	long long n;
	cin >> n;
	n %= 1500000;
	while (i <= n) {
		DP[i] = ((DP[i - 1] % MOD) + (DP[i - 2] % MOD)) % MOD;
		i++;
	}
	cout << DP[n];
}