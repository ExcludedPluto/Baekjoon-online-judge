#include <iostream>

using namespace std;

int N, arr[10];
char str[9], mini[10], maxi[10];
bool check[10], isMini;

void brute(int deep);

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> str[i];

	for (int i = 0; i < 10; i++) {
		arr[0] = i;
		check[i] = true;
		brute(0);
		check[i] = false;
	}

	cout << maxi << endl;
	cout << mini << endl;
}

void brute(int deep) {
	if (deep == N) {
		if (!isMini) {
			for (int i = 0; i < N + 1; i++)
				mini[i] = arr[i] + '0';
			isMini = true;
		}
		for (int i = 0; i < N + 1; i++)
			maxi[i] = arr[i] + '0';
		cout << "check : " << maxi << endl;
		return;
	}

	if (str[deep] == '>') {
		for (int i = 0; i <= arr[deep] - 1; i++) {
			if (!check[i]) {
				arr[deep + 1] = i;
				check[i] = true;
				brute(deep + 1);
				check[i] = false;
			}
		}
	}
	else {
		for (int i = arr[deep] + 1; i <= 9; i++) {
			if (!check[i]) {
				arr[deep + 1] = i;
				check[i] = true;
				brute(deep + 1);
				check[i] = false;
			}
		}
	}
}