#pragma once
typedef struct Point {
	int front;
	int back;
	Point* next;
} Point;

void addPoint(Point** headPoint, Point** tailPoint, int front, int back);
Point* pickPoint(Point** headPoint, Point** tailPoint);
void deletePoint(Point* point);
