#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int N, acheck[26], index, result;
string word;

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> word;
		int digit = 1;
		for (int j = word.size() - 1; j >= 0; j--) {
			if (acheck[word[j] - 'A'] == 0)
				index++;
			acheck[word[j] - 'A'] += digit;
			digit *= 10;
		}
	}
	sort(acheck, acheck + 26);

	int cur = 9 - index + 1;
	for (int i = 26 - index; i < 26; i++) {
		result += acheck[i] * cur;
		cur++;
	}
	cout << result;
}