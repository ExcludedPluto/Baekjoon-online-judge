#include <iostream>
#define MAX_N 100000

using namespace std;

int num[MAX_N];
int sumNum[MAX_N];
int N, S;

int shortestSequence(int start);

int main() {
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> num[i];

	int start = S / 10000;
	cout << shortestSequence(start);
}


int shortestSequence(int start) {
	sumNum[0] = num[0];
	for (int i = 1; i < N; i++) {
		sumNum[i] = sumNum[i - 1] + num[i];
	}

	for (int i = start; i <= N; i++) {
		int first = num[0];
		int sum = sumNum[i - 1];
		if (sum >= S)
			return i;

		for (int j = i; j < N; j++) {
			sum -= first;
			sum += num[j];
			if (sum >= S)
				return i;
			first = num[j - i + 1];
		}
	}
	return 0;
}