#include <bits/stdc++.h>

using namespace std;

int N, ans[10];
char S[10][10];
bool gotAns;

void makeArr(int deep, int beforeSum);
bool check(int deep, int beforeSum); 
void goNext(int start, int end, int deep, int bs);

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			cin >> S[i][j];

	makeArr(0, 0);
	for (int i = 0; i < N; i++)
		cout << ans[i] << " ";
}

void makeArr(int deep, int beforeSum) {
	if (deep == N) {
		gotAns = true;
		return;
	}

	switch (S[deep][deep]) {
	case '0':
		goNext(0, 0, deep, beforeSum);
		break;
	case '+':
		goNext(1, 10, deep, beforeSum);
		break;
	case '-':
		goNext(-10, -1, deep, beforeSum);
		break;
	}
}

void goNext(int start, int end, int deep, int bs) {
	for (int i = start; i <= end; i++) {
		if (gotAns)
			return;
		if (check(deep, bs + i)) {
			ans[deep] = i;
			makeArr(deep + 1, bs + i);
		}
	}
}

bool check(int deep, int sum) {
	int temp = sum;

	for (int i = 0; i < deep; i++) {
		if (S[i][deep] == '0' && temp != 0)
			return false;
		if (S[i][deep] == '+' && temp <= 0)
			return false;
		if (S[i][deep] == '-' && temp >= 0)
			return false;
		temp -= ans[i];
	}
	return true;
}