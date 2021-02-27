#include <iostream>
#include <cstring>
#define MAX_COMMAND 1000000

using namespace std;

int command[MAX_COMMAND];
int numOfCommand;
int foot[2];
int dp[5][5][MAX_COMMAND];

int getMinEnergy(int cmd);
int min(int a, int b) {
	return a < b ? a : b;
}
bool isClose(int f, int cmd);
bool isOpposite(int f, int cmd);

int main() {
	while (true) {
		cin >> command[numOfCommand];
		if (command[numOfCommand] == 0)
			break;
		numOfCommand++;
	}

	cout << getMinEnergy(0);
}

int getMinEnergy(int cmd) {
	if (cmd == numOfCommand)
		return 0;
	if (dp[foot[0]][foot[1]][cmd] != 0)
		return dp[foot[0]][foot[1]][cmd];

	int minimum = 2000000000;
	//���� �ڸ��� �ִ� ���� �ִ��� �˻�
	if (command[cmd] == foot[0] || command[cmd] == foot[1]) {
		minimum = min(minimum, getMinEnergy(cmd + 1) + 1);
	}
	else {
		//�߾ӿ� �ִ� �� Ȯ��
		if (foot[0] == 0) {
			foot[0] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 2);
			foot[0] = 0;
		}
		if (foot[1] == 0) {
			foot[1] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 2);
			foot[1] = 0;
		}

		int tempLeft = foot[0];
		int tempRight = foot[1];
		//�������� Ȯ��
		if (isClose(foot[0], command[cmd])) {
			foot[0] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 3);
			foot[0] = tempLeft;
		}
		if (isClose(foot[1], command[cmd])) {
			foot[1] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 3);
			foot[1] = tempRight;
		}
		//�ݴ�������
		if (isOpposite(foot[0], command[cmd])) {
			foot[0] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 4);
			foot[0] = tempLeft;
		}
		if (isOpposite(foot[1], command[cmd])) {
			foot[1] = command[cmd];
			minimum = min(minimum, getMinEnergy(cmd + 1) + 4);
			foot[1] = tempRight;
		}
	}
	return dp[foot[0]][foot[1]][cmd] = minimum;
}

bool isClose(int f, int cmd) {
	if (f == 1 && (cmd == 2 || cmd == 4))
		return true;
	if (f == 2 && (cmd == 1 || cmd == 3))
		return true;
	if (f == 3 && (cmd == 2 || cmd == 4))
		return true;
	if (f == 4 && (cmd == 1 || cmd == 3))
		return true;
	return false;
}

bool isOpposite(int f, int cmd) {
	if (f == 1 && cmd == 3)
		return true;
	if (f == 2 && cmd == 4)
		return true;
	if (f == 3 && cmd == 1)
		return true;
	if (f == 4 && cmd == 2)
		return true;
	return false;
}