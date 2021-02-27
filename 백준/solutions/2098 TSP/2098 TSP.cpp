#include <iostream>
#include <cstring>
#define MAX_TOWN 16
#define INFINITY 2000000123

using namespace std;

bool check[MAX_TOWN];
int dp[MAX_TOWN][1 << MAX_TOWN];
int map[MAX_TOWN][MAX_TOWN];
int numOfTown, start, endBit;

int getMinValue(int current, int bitMask);
int min(int a, int b);

int main() {
	cin >> numOfTown;
	for (int i = 0; i < numOfTown; i++)
		for (int j = 0; j < numOfTown; j++) {
			cin >> map[i][j];
		}

	endBit = (1 << numOfTown) - 1;
	memset(dp, -1, sizeof(dp));
	check[0] = true;
	start = 0;
	cout << getMinValue(0, 1);
}

int min(int a, int b) {
	return a < b ? a : b;
}

int getMinValue(int current,int bitMask) {
	if (bitMask == endBit) {
		if (map[current][start] == 0)
			return INFINITY;
		return map[current][start];
	}
	if (dp[current][bitMask] != -1)
		return dp[current][bitMask];

	int tempMin = INFINITY;
	for (int i = 0; i < numOfTown; i++) {
		if (!check[i] && map[current][i] != 0) {
			check[i] = true;
			tempMin = min(tempMin, map[current][i] + getMinValue(i, bitMask + (1 << i)));
			check[i] = false;
		}
	}
	return dp[current][bitMask] = tempMin;
}