#include <iostream>

using namespace std;

int DP[1000001];

int getResult(int n);
int minTwo(int a, int b) {
	return a < b ? a : b;
}

int main() {
	int temp;
	cin >> temp;
	getResult(temp);
	cout << DP[temp] << "\n";

	//1로 가는 수 출력
	int minResult = DP[temp];
	int cur = temp;
	while (cur >= 1) {
		cout << cur << " ";
		if (cur == 1)
			break;
		minResult--;
		if (DP[cur - 1] == minResult)
			cur -= 1;
		else if (cur % 2 == 0 && DP[cur / 2] == minResult)
			cur /= 2;
		else if (cur % 3 == 0 && DP[cur / 3] == minResult) 
			cur /= 3;
	}
}
//바텀업 방식으로 푼 코드
int getResult(int n) {
	if (DP[n] != 0)
		return DP[n];
	if (n == 1)
		return 0;

	int answer = 2000000000;
	if (n % 3 == 0)
		answer = minTwo(answer, getResult(n / 3) + 1);
	if (n % 2 == 0)
		answer = minTwo(answer, getResult(n / 2) + 1);
	answer = minTwo(answer, getResult(n - 1) + 1);

	return DP[n] = answer;
}