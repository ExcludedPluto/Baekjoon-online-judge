#include <stdio.h>
#include "pointQueue.h"
#define MAX_WIDTH 100
int width;
int area[MAX_WIDTH][MAX_WIDTH];
int tempArea[MAX_WIDTH][MAX_WIDTH] = { 0, };
int maxAreaNotSinked = 1;

void getProperties();
void figureMaxAreaNotSinked();
void initTempArea();
int getTempMaxArea( int height);
void checkAndMakeZeroCloseArea(int height, int front, int back);
void isMaxAreaAndSet(int tempMaxArea);

int main() {
	getProperties();
	figureMaxAreaNotSinked();
	printf("%d", maxAreaNotSinked);

	return 1;
}

void getProperties() {
	scanf_s("%d", &width);
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			scanf_s("%d", &area[i][j]);
}
void figureMaxAreaNotSinked() {
	//�� ���̿��� �׻� tempArea ������.
	//�� ����(1~100)���� tempMaxArea ���ϰ� �װ� ��¥ max�� ���� �ƴϸ� �׳� ����.
	//�տ������� �˻��ϴٰ� ����� ���� ���� �߰��ϸ� tempMaxArea 1�߰�(0���� ����)
	//ó���߰��ϸ� ��, �޸� �˻�-> ����� ������ ť�� �߰� -> �߰� �۾� ������ ť�� �� �͵�
	//�����鼭 �ٽ� �߰� -> �� point�� �߰� �۾��� ������ free�� �ʱ�ȭ ��Ű��, �� ����tempArea ���� 0���� �ٲ�.
	//���̻� ������ ������ ���� ��ġ���� �ٽ� �˻� ����.

	for (int height = 1; height <= 100; height++) {
		initTempArea();
		int tempMaxArea = getTempMaxArea(height);
		if (tempMaxArea == 0)
			break;
		isMaxAreaAndSet(tempMaxArea);

	}
}

void initTempArea() {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			tempArea[i][j] = area[i][j];
}
int getTempMaxArea(int height) {
	int tempMaxArea = 0;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			if (tempArea[i][j] > height) {
				tempMaxArea++;
				checkAndMakeZeroCloseArea( height, i, j);
			}

		}
	}

	return tempMaxArea;
}
void isMaxAreaAndSet(int tempMaxArea) {
	if (tempMaxArea > maxAreaNotSinked) {
		maxAreaNotSinked = tempMaxArea;
	}
}
void checkAndMakeZeroCloseArea(int height, int front, int back) {
	Point* head = NULL;
	Point* tail = NULL;
	Point* next = NULL;

	do {
		if (next != NULL) {
			front = next->front;
			back = next->back;
		}
		if (back + 1 < width)
			if (tempArea[front][back + 1] > height) {
				addPoint(&head, &tail, front, back + 1);
				tempArea[front][back + 1] = 0;
			}
		if (back - 1 >= 0)
			if (tempArea[front][back - 1] > height) {
				addPoint(&head, &tail, front, back - 1);
				tempArea[front][back - 1] = 0;
			}
		if (front + 1 < width) 
			if (tempArea[front + 1][back] > height) {
				addPoint(&head, &tail, front + 1, back);
				tempArea[front + 1][back] = 0;
			}
		if (front - 1 >= 0)
			if (tempArea[front - 1][back] > height) {
				addPoint(&head, &tail, front - 1, back);
				tempArea[front-1][back] = 0;
			}

		tempArea[front][back] = 0;

		if (next != NULL) {
			deletePoint(next);
			next = NULL;
		}

	} while ((next = pickPoint(&head, &tail)) != NULL);


}