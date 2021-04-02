#include <iostream>
#include <cstring>
#define DIV 1000000007
using namespace std;

long long N;

long long fibonachi(long long n);
void mutMatrix(long long(*)[2], long long(*)[2]);

int main() {
	cin >> N;

	cout << fibonachi(N - 1) << endl;
}

long long fibonachi(long long n) {
	long long start[2][2] = { 1,1,1,0 };
	long long result[2][2] = { 1,0,1,0 };

	while (n != 0) {
		if (n % 2 == 1) {
			mutMatrix(result, start);
			if (n == 1)
				break;
		}
		mutMatrix(start, start);
		n /= 2;
	}
	
	return result[1][0];
}
void mutMatrix(long long (*a)[2], long long(*b)[2]) {
	long long temp[2][2] = { 0, 0,0, 0 };

	for (int i = 0; i < 2; i++) 
		for (int j = 0; j < 2; j++) 
			for (int k = 0; k < 2; k++) 
				temp[i][j] = (temp[i][j] + a[i][k] * b[k][j]) % DIV;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			a[i][j] = temp[i][j];
}