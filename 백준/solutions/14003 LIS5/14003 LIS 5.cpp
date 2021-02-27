#include <iostream>
#include <algorithm>
#define MAX_LENGTH 1000001

using namespace std;

int lengthOfSequence, sequence[MAX_LENGTH], length[MAX_LENGTH], subSequence[MAX_LENGTH], longest, lis[MAX_LENGTH];

void LIS();

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> lengthOfSequence;
	for (int i = 1; i <= lengthOfSequence; i++)
		cin >> sequence[i];

	LIS();
	cout << longest << "\n";
	for (int i = 1; i <= longest; i++)
		cout << lis[i] << " ";
}

void LIS() {
	subSequence[0] = -2000000000;
	int lengthOfSub = 1;

	int longestIndex = 0;
	for (int i = 1; i <= lengthOfSequence; i++) {
		int* lb = lower_bound(subSequence, subSequence + lengthOfSub, sequence[i]);
		*lb = sequence[i];
		if (lb - subSequence == lengthOfSub) 
			length[i] = lengthOfSub++;
		else 
			length[i] = lb - subSequence;

		if (length[i] > longest) {
			longest = length[i];
			longestIndex = i;
		}
	}

	int temp = longest;
	for (int i = longestIndex; i >= 1; i--) {
		if (length[i] == temp) {
			lis[temp] = sequence[i];
			temp--;
		}
	}
}

