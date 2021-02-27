#include <iostream>
#include <cstring>
#define MAX_HOUSE 1001
#define INFINITE 2000000000

using namespace std;

int numOfHouse, house[MAX_HOUSE][3], DP[MAX_HOUSE][3], first;

int getMinCost(int before, int deep);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> numOfHouse;
	for (int i = 0; i < numOfHouse; i++) {
		cin >> house[i][0] >> house[i][1] >> house[i][2];
	}

	int minCost = INFINITE;
	for (int i = 0; i < 3; i++) {
		first = i;
		minCost = min(getMinCost(i, 1) + house[0][i], minCost);
		memset(DP, 0, sizeof(DP));
	}
	cout << minCost;
}

int getMinCost(int before, int deep) {
	if (deep == numOfHouse) {
		return 0;
	}
	if (DP[deep][before] != 0) {
		return DP[deep][before];
	}

	

	int a= INFINITE, b = INFINITE, c = INFINITE;
	if (before != 0 && (deep != numOfHouse -1 || first != 0))
		a = getMinCost(0, deep + 1) + house[deep][0];
	if (before != 1 && (deep != numOfHouse - 1 || first != 1))
		b = getMinCost(1, deep + 1) + house[deep][1];
	if (before != 2 && (deep != numOfHouse - 1 || first != 2))
		c = getMinCost(2, deep + 1) + house[deep][2];

	int tempMin = min(min(a, b), c);

	return DP[deep][before] = tempMin;
}