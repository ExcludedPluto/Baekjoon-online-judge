#include <stdlib.h>
#include <stdio.h>;
#include "pointQueue.h"

void addPoint(Point **headPoint, Point **tailPoint, int front, int back) {
	Point* point = (Point*)malloc(sizeof(Point));
	point->front = front;
	point->back = back;
	point->next = NULL;

	
	if (*headPoint == NULL) {
		*headPoint = point;
		*tailPoint = point;
	}
	else {
		(*tailPoint)->next = point;
		*tailPoint = point;
	}
}
Point* pickPoint(Point **headPoint, Point **tailPoint) {
	if (*headPoint == NULL)
		return NULL;
	Point* tempPoint = *headPoint;
	if(tempPoint->next != NULL)
		*headPoint = (*headPoint)->next;
	if (tempPoint->next == NULL) {
		*headPoint = NULL;
		*tailPoint = NULL;
	}
	return tempPoint;
}
void deletePoint(Point* point) {
	free(point);
}
