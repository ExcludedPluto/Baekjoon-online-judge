#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_LIQUID 100000


using namespace std;

int numOfLiquid;
int liquid[MAX_LIQUID];
int zerostTwo[2];

void getProperties();
void findZerostTwo();

int main() {
	getProperties();
	findZerostTwo();
	cout << liquid[zerostTwo[0]] << ' ' << liquid[zerostTwo[1]];
}

void getProperties() {
	cin >> numOfLiquid;
	for (int i = 0; i < numOfLiquid; i++)
		cin >> liquid[i];
	sort(liquid, liquid + numOfLiquid);
}

void findZerostTwo() {
	int zerostNum = 2000000000;

	int lastMinus = -1;
	for (int i = 0; i < numOfLiquid; i++)
		if (liquid[i] < 0)
			lastMinus = i;
		else
			break;
	int firstPlus = lastMinus + 1;

	if (lastMinus >= 1) {
		zerostNum = abs(liquid[lastMinus] + liquid[lastMinus - 1]);
		zerostTwo[0] = lastMinus - 1;
		zerostTwo[1] = lastMinus;
	}
	if (firstPlus < numOfLiquid - 1 && zerostNum > liquid[firstPlus] + liquid[firstPlus + 1]) {
		zerostNum = liquid[firstPlus] + liquid[firstPlus + 1];
		zerostTwo[0] = firstPlus;
		zerostTwo[1] = firstPlus + 1;
	}

	//������ ������ �� : firstPlus �� numOfLiquid �� ������. -> ���̰� 1�̹Ƿ� while���� �׻� ������� ����
	//����� ������ �� : lastMinus �� -1�̹Ƿ� ó������ for���� ������� ����
	//����� �ϳ��� �� : ���� �� �ϳ��� ����ǰ�, first��, last�� �� �ϳ��� ��ġ�� �ٲ� -> ���̰� 1�̹Ƿ� while�� �ߴ�
	//����� �ΰ� �� �� : ù��°�� ����ǰ� first�� last�� �� ù��° ��ġ�� �ٲ� -> first�� �ٲ� �� �ι�° ���� �� while�� �ߴ�, last�� �ٲ�� �ٷ� while�� �ߴ�


	for (int i = 0; i <= lastMinus; i++) {
		if (zerostNum == 0)
			break;

		int first = firstPlus-1;
		int last = numOfLiquid;
		
		while (last - first > 1) {
			int j = (first + last) / 2;
			int temp = liquid[i] + liquid[j];
			int temp2 = temp < 0 ? temp * (-1) : temp;

			if (temp2 < zerostNum) {
				zerostNum = temp2;
				zerostTwo[0] = i; 
				zerostTwo[1] = j;
			}

			if (temp > 0)
				last = j;
			else
				first = j;
		}
	}
}