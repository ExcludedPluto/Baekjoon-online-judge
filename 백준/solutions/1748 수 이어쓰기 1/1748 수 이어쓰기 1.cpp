#include <iostream>

using namespace std;

int N;

int main() {
	cin >> N;

	long long result = 0;

	int d = 1, count = 0;
	while (N / d != 0) {		// 1~9 : 1 / 10~99 : 2 / 100~999 : 3
		d *= 10;
		count++;
	}

	while (count != 0) {
		d /= 10;
		result += count * (N - d + 1);

		N = d - 1;
		count--;
	}

	cout << result;
}