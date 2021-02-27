#include <iostream>
#include <cstdio>
#include <cmath>
#define MAX_POINT 10000

using namespace std;

typedef struct Point {
	long long x;
	long long y;
} Point;

Point point[MAX_POINT];
int numOfPoint;

double getAreaOfPolygon();

int main() {
	cin >> numOfPoint;
	for (int i = 0; i < numOfPoint; i++)
		cin >> point[i].x >> point[i].y;

	printf("%.1f", getAreaOfPolygon());
}

double getAreaOfPolygon() {
	double area = 0;

	for (int i = 0; i < numOfPoint - 1; i++)
		area += ((point[i].x * point[i + 1].y) - (point[i + 1].x * point[i].y));
	area += (point[numOfPoint - 1].x * point[0].y) - (point[0].x * point[numOfPoint - 1].y);
	area = area < 0 ? (-1) * area : area;
	return area /= 2;
}

