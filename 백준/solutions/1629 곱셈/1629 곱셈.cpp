#include <iostream>

using namespace std;

long long A, B, C;
long long result = 1;


int main() {
	cin >> A >> B >> C;

	while (B != 0) {
		if (B % 2 == 1) {
			result = (result * A) % C;
		}
		A = (A * A) % C;
		B /= 2;
	}
	cout <<  result % C;
}