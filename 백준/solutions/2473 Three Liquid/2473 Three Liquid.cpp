#include <iostream>
#include <algorithm>
#include <set>
#define MAX_LIQUID 5000

using namespace std;

int liquid[MAX_LIQUID];
int numOfLiquid;
int threeLiquid[3];

void getZerost();
int abs(int a) {
	return a < 0 ? (-1) * a : a;
}
void setThreeLiquid(int f, int s, int t) {
	threeLiquid[0] = f;
	threeLiquid[1] = s;
	threeLiquid[2] = t;
}

int main() {
	cin >> numOfLiquid;
	for (int i = 0; i < numOfLiquid; i++)
		cin >> liquid[i];

	getZerost();
	for (int i = 0; i < 3; i++)
		cout << threeLiquid[i] << " ";
}

void getZerost() {
	sort(liquid, &liquid[numOfLiquid]);
	int firstPlus = numOfLiquid;
	for (int i = 0; i < numOfLiquid; i++)
		if (liquid[i] > 0) {
			firstPlus = i;
			break;
		}
	if (firstPlus == numOfLiquid) {
		setThreeLiquid(liquid[numOfLiquid - 3], liquid[numOfLiquid - 2], liquid[numOfLiquid - 1]);
		return;
	}
	if (firstPlus == 0) {
		setThreeLiquid(liquid[0], liquid[1], liquid[2]);
		return;
	}

	int zerostValue = 2000000213;
	if (firstPlus > 2 && firstPlus <= numOfLiquid - 3) {
		if (abs(liquid[firstPlus-3] + liquid[firstPlus-2] + liquid[firstPlus-1]) < liquid[firstPlus] + liquid[firstPlus + 1] + liquid[firstPlus + 2]) {
			zerostValue = abs(liquid[firstPlus - 3] + liquid[firstPlus - 2] + liquid[firstPlus - 1]);
			setThreeLiquid(liquid[firstPlus - 3], liquid[firstPlus - 2], liquid[firstPlus - 1]);
		}
		else {
			zerostValue = liquid[firstPlus] + liquid[firstPlus + 1] + liquid[firstPlus + 2];
			setThreeLiquid(liquid[firstPlus], liquid[firstPlus + 1] ,liquid[firstPlus + 2]);
		}
	}
	else if (firstPlus > 2) {
		zerostValue = abs(liquid[firstPlus - 3] + liquid[firstPlus - 2] + liquid[firstPlus - 1]);
		setThreeLiquid(liquid[firstPlus - 3], liquid[firstPlus - 2], liquid[firstPlus - 1]);
	}
	else if (firstPlus <= numOfLiquid - 3) {
		zerostValue = liquid[firstPlus] + liquid[firstPlus + 1] + liquid[firstPlus + 2];
		setThreeLiquid(liquid[firstPlus], liquid[firstPlus + 1], liquid[firstPlus + 2]);
	}

	//-97 -6 -2 6 98
	//음수 2개, 양수 1개
	if (firstPlus >= 2) {
		set<int> s;
		for (int i = firstPlus; i < numOfLiquid; i++)
			s.insert(liquid[i]);
		for (int first = 0; first <= firstPlus - 2; first++) {
			for (int second = first + 1; second <= firstPlus - 1; second++) {
				int cur = liquid[first] + liquid[second];
				set<int>::iterator iter = s.find(abs(cur));
				if (iter == s.end()) {
					iter = s.insert(abs(cur)).first;
					iter = s.erase(iter);
					if (iter != s.end() &&(cur + *iter < zerostValue)) {
						zerostValue = cur + *iter;
						setThreeLiquid(liquid[first], liquid[second], *iter);
					}
					if (iter != s.begin()) {
						iter--;
						if (abs(cur + *iter) < zerostValue) {
							zerostValue = abs(cur + *iter);
							setThreeLiquid(liquid[first], liquid[second], *iter);
						}
					}
				}
				else {
					setThreeLiquid(liquid[first], liquid[second], *iter);
					return;
				}
			}
		}
	}
	//음수 1개, 양수 2개
	if (firstPlus < numOfLiquid - 1) {
		set<int> s;
		for (int i = 0; i < firstPlus; i++)
			s.insert(liquid[i]);
		for (int first = 0; first <= firstPlus - 1; first++) {
			for (int second = firstPlus; second < numOfLiquid - 1; second++) {
				int cur = liquid[first] + liquid[second];
				set<int>::iterator iter = s.find(0 - cur);
				if (iter == s.end()) {
					iter = s.insert(0 - cur).first;
					iter = s.erase(iter);
					if (iter != s.end() && (cur + *iter < zerostValue)) {
						zerostValue = cur + *iter;
						setThreeLiquid(*iter, liquid[first], liquid[second]);
					}
					if (iter != s.begin()) {
						iter--;
						if (abs(cur + *iter) < zerostValue) {
							zerostValue = abs(cur + *iter);
							setThreeLiquid(*iter, liquid[first], liquid[second]);
						}
					}
				}
				else {
					setThreeLiquid(*iter, liquid[first], liquid[second]);
					return;
				}
			}
		}

	}
}