#include <iostream>
#define MAX_CLASS 1000000

using namespace std;

int testClass[MAX_CLASS];
int numOfClass;
int chief;
int second;

int main() {
	cin >> numOfClass;
	for (int i = 0; i < numOfClass; i++)
		cin >> testClass[i];
	cin >> chief >> second;

	long long need = numOfClass;
	for (int i = 0; i < numOfClass; i++) {
		testClass[i] -= chief;
		if (testClass[i] <= 0)
			continue;
		int temp = testClass[i] / second;
		need += temp;
		testClass[i] -= temp * second;
		need += (testClass[i] > 0 ? 1 : 0);
	}

	cout << need;
}