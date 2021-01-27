#include <iostream>
#include <vector>
#include <cstring>
#define MAX_MINUTE 100000
#define DIVIDE 1000000007

using namespace std;

//0 : ����, 1 : ����, 2 : �̷�, 3 : �ž� , 4: �Ѱ���, 
//5 : ����, 6 : ����, 7 : �л�
vector<vector<int>> map = { {1,2}, {0,2,3}, {0,1,3,4}, {1,2,4,5}, {2,3,5,6}, {3,4,7}, {4,7}, {5,6} };
int D;
int DP[8][MAX_MINUTE];

int getMin(int num, int minute);

int main() {
	memset(DP, -1, sizeof(DP));
	cin >> D;
	cout << getMin(0, 0) << endl;
}
/*
a �� x�� ����� ������ Ƚ����
	a�� ����� ��� b�� x+1�� ����� ������ Ƚ���� ����
*/

int getMin(int num, int minute) {
	if (minute == D)
		return num == 0 ? 1 : 0;
	if (DP[num][minute] != -1)
		return DP[num][minute];

	long long result = 0;
	int length = map[num].size();
	for (int i = 0; i < length; i++)
		result += getMin(map[num][i], minute + 1);

	return DP[num][minute] = result % DIVIDE;
}