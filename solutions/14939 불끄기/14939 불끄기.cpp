#include <bits/stdc++.h>

using namespace std;

bool smap[10][10], tempMap[10][10];

int brute();
int rest();
void swit(int r, int c);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	for (int i = 0; i < 10; i++) {
		char t;
		for (int j = 0; j < 10; j++) {
			cin >> t;
			if (t == '#')
				smap[i][j] = 0;
			else if (t == 'O')
				smap[i][j] = 1;
		}
	} 

	int result = brute();
	if (result >= 2000000000)
		cout << -1;
	else
		cout << result;

}

int brute() {
	int result = 2000000000;
	for (int i = 0; i <= 1023; i++) {
		memcpy(tempMap, smap, sizeof(smap));

		int k = 0, count = 0;
		for (int j = 512; j >= 1; j /= 2) {
			if (i & j) {
				swit(0, k);
				count++;
			}
			k++;
		}
		int r = rest();
		result = min(result, count + r);
	}

	return result;
}

int rest() {
	int count = 0;
	for (int i = 1; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (tempMap[i - 1][j]) {
				swit(i, j);
				count++;
			}

	for (int j = 0; j < 10; j++) {
		if (tempMap[9][j])
			count = 2000000000;
	}

	return count;
}

void swit(int r, int c) {
	tempMap[r][c] = !(tempMap[r][c]);
	if (r > 0)
		tempMap[r - 1][c] = !(tempMap[r - 1][c]);
	if (c < 9 )
		tempMap[r][c + 1] = !(tempMap[r][c + 1]);
	if (r < 9)
		tempMap[r + 1][c] = !(tempMap[r + 1][c]);
	if (c > 0)
		tempMap[r][c - 1] = !(tempMap[r][c - 1]);
}