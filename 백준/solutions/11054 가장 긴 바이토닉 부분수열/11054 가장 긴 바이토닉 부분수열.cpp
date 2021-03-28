#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N, num[1001], l[1001], r[1001], t[1001], ind;

int generateLIS();
void left();
void right();

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];

	cout << generateLIS() << endl;
}

int generateLIS() {
	left();
	memset(t, 0, sizeof(t));
	right();

	for (int i = 0; i < N; i++) {
		cout << l[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < N; i++) {
		cout << r[i] << " ";
	}
	cout << endl;

	int result = 0;
	for (int i = 0; i < N; i++) {
		int c = l[i] + r[i] + 1;
		result = result > c ? result : c;
	}
	return result;
}

void left() {
	l[0] = 0;
	t[0] = num[0];
	ind = 1;
	for (int i = 1; i < N; i++) {
		int* p = lower_bound(&t[0], &t[ind], num[i]);

		if (*p == num[i])
			l[i] = p - t;
		else {
			l[i] = p - t;
			*p = num[i];
			if (p - t == ind)
				ind++;
		}
	}
	for (int i = 0; i < N; i++)
		cout << t[i] << " ";
	cout << endl;
}

void right() {
	r[N - 1] = 0;
	t[0] = num[N - 1];
	ind = 1;
	for (int i = N - 2; i >= 0; i--) {
		int* p = lower_bound(&t[0], &t[ind], num[i]);

		if (*p == num[i])
			r[i] = p - t;
		else {
			r[i] = p - t;
			*p = num[i];
			if (p - t == ind)
				ind++;
		}
	}
	for (int i = 0; i < N; i++)
		cout << t[i] << " ";
	cout << endl;
}