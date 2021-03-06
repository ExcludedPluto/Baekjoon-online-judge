#include <iostream>

using namespace std;

int N, M, party[51][51];
bool knowTruth[51], alreadyCheck[51];

int getAns();
void makeKnow();

int main() {
	cin >> N >> M;
	int t;
	cin >> t;
	while(t--) {
		int a;
		cin >> a;
		knowTruth[a] = true;
	}

	for (int i = 0; i < M; i++) {
		int n;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> party[i][j];
	}
	makeKnow();
	cout << getAns();
}

void makeKnow() {
	bool change = true;
	while (change) {
		change = false;

		for (int i = 0; i < M; i++) {
			if (alreadyCheck[i])
				continue;

			int index = 0;
			bool check = false;
			while (party[i][index] != 0) {
				if (knowTruth[party[i][index]]) {
					check = true;
					break;
				}
				index++;
			}

			if (check) {
				change = true;
				alreadyCheck[i] = true;
				index = 0;
				while (party[i][index] != 0) {
					knowTruth[party[i][index]] = true;
					index++;
				}
			}
		}
	}
}

int getAns() {
	int result = 0;
	for (int i = 0; i < M; i++) {
		int index = 0;
		bool check = true;
		while (party[i][index] != 0) {
			if (knowTruth[party[i][index]]) {
				check = false;
				break;
			}
			index++;
		}
		if (check)
			result++;
	}
	return result;
}