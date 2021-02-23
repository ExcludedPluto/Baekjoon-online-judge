#include <bits/stdc++.h>
#define MAX_WIRE 100001

using namespace std;

struct Wire {
	int a;
	int b;
	bool check;
	bool operator <(Wire s) {
		return a < s.a;
	}
};

Wire wire[MAX_WIRE];
int numOfWire, length[500001], save[500001], numOfSave;

void LIS();

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> numOfWire;
	for (int i = 0; i < numOfWire; i++)
		cin  >> wire[i].a >> wire[i].b;

	sort(wire, wire + numOfWire);

	LIS();
}

void LIS() {
	int result = 0, index = 0;
	for (int i = 0; i < numOfWire; i++) {
		int *lb = lower_bound(save, save + numOfSave, wire[i].b);
		
		length[wire[i].a] = lb - save + 1;
		*lb = wire[i].b;

		if (length[wire[i].a] ==  numOfSave + 1)
			numOfSave++;

		if (result < length[wire[i].a]) {
			result = length[wire[i].a];
			index = i;
		}
	}

	cout << numOfWire - result << "\n";
	for (int i = index; i >= 0; i--) {
		if (result <= 0)
			break;
		if (length[wire[i].a] == result) {
			wire[i].check = true;
			result--;
		}
	}
	for (int i = 0; i < numOfWire; i++)
		if (!wire[i].check)
			cout << wire[i].a << "\n";
}