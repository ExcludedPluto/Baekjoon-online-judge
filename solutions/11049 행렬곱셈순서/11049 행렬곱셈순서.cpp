#include <iostream>
#define MAX_MATRIX 501

using namespace std;

int numOfMatrix, matrix[MAX_MATRIX][2], DP[MAX_MATRIX][MAX_MATRIX];

int getMinCalulate(int start, int end);
long long min(long long a, int b) {
	return a < b ? a : b;
}

int main() {
	cin >> numOfMatrix;

	for (int i = 0; i < numOfMatrix; i++)
		cin >> matrix[i][0] >> matrix[i][1];
	
	cout << getMinCalulate(0, numOfMatrix - 1);
}

int getMinCalulate(int start, int end) {
	if (start == end)
		return 0;
	if (DP[start][end] != 0)
		return DP[start][end];

	long long result = 3000000000;
	for (int i = start; i < end; i++) {
		result = min(result, getMinCalulate(start, i) + getMinCalulate(i + 1, end) + (matrix[start][0]*matrix[i][1]*matrix[end][1]));

	}

	return DP[start][end] = result;
}
