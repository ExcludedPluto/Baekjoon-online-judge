#include <iostream>
#include <cstring>
using namespace std;

long long N, B;
long long map[5][5], result[5][5] = { {1,0,0,0,0}, {0,1,0,0,0}, {0,0,1,0,0}, {0,0,0,1,0}, {0,0,0,0,1} };

void multiMap(bool isResult);
void powerMap();

int main() {
	cin >> N >> B;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	powerMap();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << result[i][j] << " ";
		cout << endl;
	}
}

void powerMap() {
	while (B >= 1) {
		if (B % 2 == 1) {
			multiMap(true);
			if (B == 1)
				break;
		}
		multiMap(false);
		B /= 2;
	}
}

void multiMap(bool isResult) {
	long long temp[5][5];
	memset(temp, 0, sizeof(temp));

	if (isResult) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++)
					temp[i][j] = ((temp[i][j] % 1000)+ ((result[i][k] * map[k][j]) % 1000));
				temp[i][j] %= 1000;
			}
		}
		memcpy(result, temp, sizeof(temp));
	}
	else {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++)
					temp[i][j] = ((temp[i][j] % 1000) + ((map[i][k] * map[k][j]) % 1000));
				temp[i][j] %= 1000;
			}
		}
		memcpy(map, temp, sizeof(temp));
	}
}