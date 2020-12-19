#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>

using namespace std;

typedef struct Point {
	int x;
	int y;
} Point;

vector<vector<Point>> tc;
vector<Point> currentPoint;
int sumOfEveryX, sumOfEveryY;

void generateTc();
long double solveSingleTC(vector<int> choosed, int deep);

int main() {
	int numOfTc;
	cin >> numOfTc;
	for (int i = 0; i < numOfTc; i++) {
		int numOfPoint;
		cin >> numOfPoint;
		vector<Point> tempPoint;
		for (int j = 0; j < numOfPoint; j++) {
			int x, y;
			cin >> x >> y;
			tempPoint.push_back({ x, y });
		}
		tc.push_back(tempPoint);
	}
	generateTc();
}

void generateTc() {
	for (int i = 0; i < tc.size(); i++) {
		currentPoint = tc[i];
		sumOfEveryX = 0;
		sumOfEveryY = 0;
		for (int j = 0; j < currentPoint.size(); j++) {
			sumOfEveryX += currentPoint[j].x;
			sumOfEveryY += currentPoint[j].y;
		}
		vector<int> choosed;
		cout << "test" << endl;
		cout.precision(50);
		cout << solveSingleTC(choosed, 0) << endl;
	}
}

long double solveSingleTC(vector<int> choosed, int deep) {
	if (choosed.size() == currentPoint.size() / 2) {
		long long sumOfChoosedX = 0;
		long long sumOfChoosedY = 0;
		for (int i = 0; i < choosed.size(); i++) {
			sumOfChoosedX += currentPoint[choosed[i]].x;
			sumOfChoosedY += currentPoint[choosed[i]].y;
		}
		long long length = (sumOfEveryX - 2 * sumOfChoosedX) * (sumOfEveryX - 2 * sumOfChoosedX) + 
							(sumOfEveryY - 2 * sumOfChoosedY) * (sumOfEveryY - 2 * sumOfChoosedY);
		return sqrt(length);
	}
	else if (currentPoint.size() - deep < (currentPoint.size() / 2) - choosed.size())
		return 2000000000;

	long double a = solveSingleTC(choosed, deep + 1);
	choosed.push_back(deep);
	long double b = solveSingleTC(choosed, deep + 1);
	return a < b ? a : b;
}