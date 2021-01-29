#include <iostream>
#define MAX 4000001

using namespace std;

int prime[290000], tempPrime[MAX];
int N, numOfPrime = 0;

void generatePrime();
int getResult();

int main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin >> N;
	generatePrime();
	cout << getResult();
}

void generatePrime() {
	for (int i = 2; i <= N; i++)
		tempPrime[i] = i;

	for (int i = 2; i <= N / 2; i++) {
		if (tempPrime[i] != -1)
			for (int j = 2 * i; j <= N; j += i) {
				tempPrime[j] = -1;
			}
	}
	for (int i = 2; i <= N; i++)
		if (tempPrime[i] != -1)
			prime[numOfPrime++] = tempPrime[i];
}

int getResult() {
	int start = 0, end = 1;
	int sum = prime[0], count = 0;


	while (start < end) {
		if (sum == N) {
			count++;
			sum -= prime[start++];
		}
		else if (sum < N) {
			if (end == numOfPrime)
				break;
			sum += prime[end++];
		}
		else 
			sum -= prime[start++];
	}
	return count;
}