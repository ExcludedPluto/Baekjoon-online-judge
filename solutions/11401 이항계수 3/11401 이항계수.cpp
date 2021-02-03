#include <iostream>
#define DIVIDE 1000000007

using namespace std;

long long getCoefficient(int n, int k);
long long getPower(long long n, long long k);

int main() {
	int n, k;
	cin >> n >> k;
	cout << getCoefficient(n, k) << endl;

}

long long getCoefficient(int n, int k) {
	if (k == 0 || k == n)
		return 1;

	long long top = 1, bottom = 1, bottom2 = 1;

	for (int i = n; i >= 1; i--)
		top = (top * i) % DIVIDE;
	top %= DIVIDE;
	for (int i = k; i >= 1; i--)
		bottom = (bottom * i) % DIVIDE;
	bottom %= DIVIDE;
	for (int i = n - k; i >= 1; i--)
		bottom2 = (bottom2 * i) % DIVIDE;
	bottom2 %= DIVIDE;


	bottom = (bottom * bottom2) % DIVIDE;
	top %= DIVIDE;

	return (top * (getPower(bottom, DIVIDE - 2))) % DIVIDE;
}

long long getPower(long long n, long long k) {
	long long result = 1, temp = n;

	while (k > 0) {
		if (k % 2 == 1) {
			result = (result * temp) % DIVIDE;
		}
		temp = (temp * temp) % DIVIDE;
		k /= 2;
	}

	return result % DIVIDE;
}