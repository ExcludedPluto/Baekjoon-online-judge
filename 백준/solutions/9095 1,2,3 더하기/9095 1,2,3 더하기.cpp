#include <iostream>

using namespace std;

int tc;
long long save[12];

long long dp(int n);

int main() {
	cin >> tc;

	while (tc--) {
		int n;
		cin >> n;
		cout << dp(n) << endl;
	}
}

long long dp(int n) {
	if (n < 0)
		return 0;
	if (n == 0) {
		return 1;
	}
	if (save[n] != 0)
		return save[n];

	return save[n] = dp(n - 3) + dp(n-2) + dp(n-1);

}