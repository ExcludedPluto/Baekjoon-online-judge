#include <iostream>
#include <cstring>
#define MAX_LENGTH 2001

using namespace std;

int n[MAX_LENGTH], numOfN, DP[MAX_LENGTH][MAX_LENGTH];

bool isPalindrome(int from, int to);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> numOfN;
	for (int i = 1; i <= numOfN; i++) {
		cin >> n[i];
	}
	int numOfQ;
	cin >> numOfQ;
	for (int i = 0; i < numOfQ; i++) {
		int from, to;
		cin >> from >> to;
		if (isPalindrome(from, to))
			cout << 1 << '\n';
		else
			cout << 0 << '\n';
	}
}

bool isPalindrome(int from, int to) {
	if (DP[from][to] == 1)
		return true;
	else if (DP[from][to] == 2)
		return false;
	else {
		int fromEnd = (from + to) / 2, toEnd, tempFromEnd, temptoEnd;
		if ((from + to) % 2 == 0) 
			toEnd = (from + to) / 2;
		else 
			toEnd = fromEnd + 1;

		bool check = true;
		for (int i = from, j = to; i <= fromEnd && j >= toEnd; i++, j--) {
			if (DP[i][j] == 2) {
				check = false;
				tempFromEnd = i;
				temptoEnd = j;
				break;
			}
			if (DP[i][j] == 1)
				break;
			if (n[i] != n[j]) {
				check = false;
				tempFromEnd = i;
				temptoEnd = j;
				break;
			}
		}

		if (check) {
			for (int i = from, j = to; i <= fromEnd && j >= toEnd; i++, j--) {
				if (DP[i][j] != 1)
					DP[i][j] = 1;
				else
					break;
			}
			return true;
		}
		else {
			for (int i = from, j = to; i <= tempFromEnd && j >= temptoEnd; i++, j--) {
				DP[i][j] = 2;
			}
			return false;
		}
	}
}