#include <iostream>
#include <string>
#define MAX_LENGTH 2500

using namespace std;
//2차원 배열로 모든 팰린드롬 저장
//첫번째 줄에 팰린드롬인것을 하나씩 넣음
//그리고 오른쪽 아래로 내려가며 가능한 것을 최대한 넣자.
//ex) map[0][0] 은 무조건 팰린드롬이니 고름 -> map[1][1]에서 가장가까운 팰린드롬 고름 map[1][1] -> map[2][2] -> ..... 총길이 2500, -> map[1][2] ...map[1][3].. 이렇게 진행?
//위처럼 진행할 경우 2500*2500 + 2499*2499 + ... 총 26억 계산 -> 시간초과
//가장가까운이 아닌, 가장 먼곳부터 골라보자. map[0][n] ... 그리고 길이가 이미고른 길이보다 길면 중간종료 하는 식으로?
//하지만 최악의 경우 또 26억이 됨
//DP  = 위 계산을 바텀업방식으로 하여 DP[x] 에 길이를 저장하는 방식으로 해보자

int length, DP[MAX_LENGTH];
char input[MAX_LENGTH];
bool palindrome[MAX_LENGTH][MAX_LENGTH];

void makePalindrome();
bool isPalindrome(int start, int end);
void recordPalindrome(int start, int end);
int getMinSplit(int start);
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	string tempInput;
	cin >> tempInput;
	length = tempInput.size();
	for (int i = 0; i < tempInput.size(); i++) 
		input[i] = tempInput[i];

	makePalindrome();
	cout << getMinSplit(0);
	
}

void makePalindrome() {
	for (int i = 0; i < length; i++) {
		for (int j = length - 1; j >= i; j--) {
			if (palindrome[i][j] != 0)
				continue;

			if (isPalindrome(i, j))
				recordPalindrome(i, j);
			else
				palindrome[i][j] = 0;
		}
	}
}

bool isPalindrome(int start, int end) {
	for (; start < end; start++, end--)
		if (input[start] != input[end])
			return false;

	return true;
}

void recordPalindrome(int start, int end) {
	for (; start <= end; start++, end--)
		palindrome[start][end] = 1;
}

int getMinSplit(int start) {
	if (start == length) 
		return 0;
	if (DP[start])
		return DP[start];

	int result = 200000000;

	for (int i = length-1; i >= start; i--)
		if (palindrome[start][i])
			result = min(result, getMinSplit(i + 1) + 1);

	return DP[start] = result;
}