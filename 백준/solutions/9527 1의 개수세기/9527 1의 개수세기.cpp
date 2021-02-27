#include <iostream>
#include <cmath>

using namespace std;

long long a, b;
long long DP[55];

long long getN(int N);
long long countOne(long long end);
long long getRest(long long start, long long end);

int main() {
	cin >> a >> b;
	DP[0] = 1;

	cout << countOne(b) - countOne(a-1) << endl;
}

long long countOne(long long end) {
	if (end <= 2)
		return end;

	int n = 0;
	long long temp = 1;
	while (temp < end) {
		temp *= 2;
		n++;
	}
	if (temp - end <=1)
		n -= 1;
	else
		n -= 2;

	long long result = 0;
	for (int i = 0; i <= n; i++)
		result += getN(i);
	  
	result += getRest(pow(2, n+1), end);

	return result;
}

long long getN(int N) {
	if (N == 0)
		return 1;
	if (DP[N] != 0)
		return DP[N];

	long long result = pow(2, N);
	for (int i = N - 1; i >= 0; i--)
		result += getN(i);

	return DP[N] = result;
}

long long getRest(long long start, long long end) {
	if (start > end)
		return 0;

	return end - start + 1 + countOne(end - start);
}