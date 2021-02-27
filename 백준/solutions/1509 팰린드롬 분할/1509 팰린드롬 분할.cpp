#include <iostream>
#include <string>
#define MAX_LENGTH 2500

using namespace std;
//2���� �迭�� ��� �Ӹ���� ����
//ù��° �ٿ� �Ӹ�����ΰ��� �ϳ��� ����
//�׸��� ������ �Ʒ��� �������� ������ ���� �ִ��� ����.
//ex) map[0][0] �� ������ �Ӹ�����̴� �� -> map[1][1]���� ���尡��� �Ӹ���� �� map[1][1] -> map[2][2] -> ..... �ѱ��� 2500, -> map[1][2] ...map[1][3].. �̷��� ����?
//��ó�� ������ ��� 2500*2500 + 2499*2499 + ... �� 26�� ��� -> �ð��ʰ�
//���尡����� �ƴ�, ���� �հ����� �����. map[0][n] ... �׸��� ���̰� �̹̰� ���̺��� ��� �߰����� �ϴ� ������?
//������ �־��� ��� �� 26���� ��
//DP  = �� ����� ���Ҿ�������� �Ͽ� DP[x] �� ���̸� �����ϴ� ������� �غ���

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