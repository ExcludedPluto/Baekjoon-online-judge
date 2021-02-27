#include <iostream>
#include <cstring>
#define MAX_LENGTH 1000
using namespace std;

char a[MAX_LENGTH], b[MAX_LENGTH], lcs[MAX_LENGTH];
int map[MAX_LENGTH + 1][MAX_LENGTH + 1];
int al, bl, numOfLCS;

void getLCS();
int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin.getline(a, MAX_LENGTH+1);
	cin.getline(b, MAX_LENGTH+1);
	for (int i = 0; i < MAX_LENGTH; i++)
		if (a[i] != 0)
			al++;
		else
			break;
	for (int i = 0; i < MAX_LENGTH; i++)
		if (b[i] != 0)
			bl++;
		else
			break;

	getLCS();
	cout << numOfLCS << endl;
	for (int i = numOfLCS-1; i >= 0; i--)
		cout << lcs[i];
	cout << endl;
}

void getLCS() {
	for (int i = 1; i <= bl; i++) {
		for (int j = 1; j <= al; j++) {
			if (b[i-1] == a[j-1])
				map[i][j] = map[i-1][j-1]+ 1;
			else
				map[i][j] = max(map[i - 1][j], map[i][j - 1]);
		}
	}
	int count = 0,start = al, before = map[bl][al]+1;
	for (int i = bl; i >= 1; i--) {
		for (int j = start; j >= 1; j--) {
			if (before - 1 != map[i][j])
				break;
			if (map[i][j - 1] != map[i][j] && b[i - 1] == a[j - 1]) {
				lcs[count++] = a[j - 1];
				start = j - 1;
				before = map[i][j];
				break;
			}
		}
		if (start == 0)
			break;
	}
	numOfLCS = count;
}

