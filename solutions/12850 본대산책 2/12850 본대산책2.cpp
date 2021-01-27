#include <iostream>
#include <cstring>
#define DIVIDE 1000000007

using namespace std;

long long map[8][8] = {
	{0,1,1,0,0,0,0,0},
	{1,0,1,1,0,0,0,0},
	{1,1,0,1,1,0,0,0},
	{0,1,1,0,1,1,0,0},
	{0,0,1,1,0,1,1,0},
	{0,0,0,1,1,0,0,1},
	{0,0,0,0,1,0,0,1},
	{0,0,0,0,0,1,1,0}
};

int D;

long long mulMap(int D);

int main() {
	cin >> D;
	cout << mulMap(D) << endl;
}

long long mulMap(int D) {
	long long tempMap[8][8] = {
	{1,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,1}
	};
	long long emptyMap[8][8];

	while (D > 0) {
		if (D % 2 == 1) {
			memset(emptyMap, 0, sizeof(emptyMap));
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					for (int k = 0; k < 8; k++)
						emptyMap[i][j] = (emptyMap[i][j] + (tempMap[i][k] * map[k][j])) % DIVIDE;
			memcpy(tempMap, emptyMap, sizeof(emptyMap));
		}
		memset(emptyMap, 0, sizeof(emptyMap));
		for (int i = 0; i < 8; i++) 
			for (int j = 0; j < 8; j++) 
				for (int k = 0; k < 8; k++) 
					emptyMap[i][j] = (emptyMap[i][j] + (map[i][k] * map[k][j])) % DIVIDE;

		memcpy(map, emptyMap, sizeof(tempMap));
		D /= 2;
	}

	return tempMap[0][0];
}

