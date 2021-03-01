#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int to;
bool isable[10];

int pushButton();
int check(int cur);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	cin >> to;

	int n, t;
	cin >> n;
	memset(isable, 1, sizeof(isable));
	for (int i = 0; i < n; i++) {
		cin >> t;
		isable[t] = false;
	}

	cout << min(abs(100 - to), pushButton());
}


int pushButton() {
	int result = 2000000000, end = to * 10;

	for (int i = 0; i <= end; i++) {
		int length = check(i);
		if(length != -1)
			result = min(result, abs(to - i) + length);
	}

	return result;
}

int check(int cur) {
	int t = 10, index = 0, end = cur * 10;

	if (end == 0)
		end = 10;

	while (t <= end) {
		int c = cur % t;
		c = c / (t / 10);

		if (!isable[c])
			return -1;

		t *= 10;
		index++;
	}

	return index;
}