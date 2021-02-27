#include <iostream>

using namespace std;

int numOfObject, weight, DP[101][100001];

int main() {
	cin >> numOfObject >> weight;
	for (int i = 1; i <= numOfObject; i++) {
		int w, v;
		cin >> w >> v;
		for (int j = 1; j <= weight; j++) {
			if (j >= w)
				DP[i][j] = DP[i - 1][j - w] + v > DP[i - 1][j] ? DP[i - 1][j - w] + v : DP[i - 1][j];
			else
				DP[i][j] = DP[i - 1][j];
		}
	}
	cout << DP[numOfObject][weight];
}