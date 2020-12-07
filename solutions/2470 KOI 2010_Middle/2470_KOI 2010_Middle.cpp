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

	//음수만 들어왔을 때 : firstPlus 가 numOfLiquid 와 같아짐. -> 차이가 1이므로 while문은 항상 실행되지 않음
	//양수만 들어왔을 때 : lastMinus 가 -1이므로 처음부터 for문이 실행되지 않음
	//양수가 하나일 때 : 먼저 그 하나가 실행되고, first든, last든 그 하나의 위치로 바뀜 -> 차이가 1이므로 while문 중단
	//양수가 두개 일 때 : 첫번째가 실행되고 first든 last든 그 첫번째 위치로 바뀜 -> first가 바뀔 시 두번째 실행 후 while문 중단, last가 바뀔시 바로 while문 중단


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