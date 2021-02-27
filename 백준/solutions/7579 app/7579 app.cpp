#include <iostream>
#define MAX_N 100
#define MAX_MEMORY 10000000

using namespace std;

int numOfApp, a[MAX_N], c[MAX_N], m, maxValue;
int DP[105][10020];

int getMin();
int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin >> numOfApp >> m;
	for (int i = 0; i < numOfApp; i++)
		cin >> a[i];
	for (int i = 0; i < numOfApp; i++) {
		cin >> c[i];
		maxValue += c[i];
	}

	cout << getMin();
}

int getMin(){
	for (int i = 1; i <= numOfApp; i++) {
		for (int j = 1; j <= maxValue; j++) {
			if (c[i-1] > j)
				DP[i][j] = DP[i - 1][j];
			else
				DP[i][j] = max(a[i-1] + DP[i - 1][j - c[i-1]], DP[i - 1][j]);
		}
	}

	int minValue = 2000000000;
	for (int i = 0; i <= numOfApp; i++) {
		for (int j = 0; j <= maxValue; j++) {
			if (DP[i][j] >= m && minValue > j)
				minValue = j;
		}
	}
	return minValue;
}