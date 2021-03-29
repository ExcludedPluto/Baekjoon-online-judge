#include <iostream>
#include <cstring>
using namespace std;

int N, K, num[30], ans[30];
bool save[31][31][31][450], got;

void DP(int d, int a, int b, int n);

int main() {
	cin >> N >> K;
	memset(num, -1, sizeof(num));
	memset(ans, -1, sizeof(ans));

	DP(0, 0, 0, 0);
	if (!got)
		cout << -1 << endl;
	else {
		for (int i = 0; i < N; i++) {
			if (ans[i] == 0)
				cout << 'A';
			else if (ans[i] == 1)
				cout << 'B';
			else if (ans[i] == 2)
				cout << 'C';
		}
	}
}

void DP(int d, int a, int b, int n) {
	if (d == N) {
		if (n == K) {
			got = true;
			memcpy(ans, num, sizeof(num));
		}
		return;
	}
	if (save[d][a][b][n])
		return;
	save[d][a][b][n] = true;

	if (got)
		return;

	num[d] = 0;
	DP(d + 1, a + 1, b, n);
	if (!got) {
		num[d] = 1;
		DP(d + 1, a, b + 1, n + a);
	}
	if (!got) {
		num[d] = 2;
		DP(d + 1, a, b, n + a + b);
	}
	num[d] = -1;
}