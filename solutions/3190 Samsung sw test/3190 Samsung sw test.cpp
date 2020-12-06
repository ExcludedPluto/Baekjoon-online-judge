#include <iostream>
#include <vector>
#include <cstring>
#define MAX_APPLE 100
#define MAX_DIRECTION 100

using namespace std;

typedef struct Location {
	int row;
	int col;
} Location;
typedef struct Direction {
	int second;
	char direction;
} Direction;

int width;
int numOfApple;
bool appleMap[MAX_APPLE][MAX_APPLE];
int numOfChange;
Direction direction[MAX_DIRECTION];

void getProperties();
int getSecond();

int main() {
	getProperties();
	cout << getSecond();
}

void getProperties() {
	cin >> width;
	cin >> numOfApple;
	memset(appleMap, 0, sizeof(bool) * MAX_APPLE * MAX_APPLE);
	for (int i = 0; i < numOfApple; i++) {
		int row, col;
		cin >> row >> col;
		appleMap[row - 1][col - 1] = true;
	}

	cin >> numOfChange;
	for (int i = 0; i < numOfChange; i++) {
		cin >> direction[i].second >> direction[i].direction;
	}
}

int getSecond() {
	int second = 0;
	vector<Location> snake;
	snake.push_back({ 0, 0 });
	int currentDirection = 2;
	int directionIndex = 0;
	bool isEnd = false;

	//현재 헤드 제일 뒤에, 꼬리는 제일 앞에
	while (!isEnd) {
		second++;
		Location s = snake.back();
		if (currentDirection == 1)
			snake.push_back({ s.row - 1, s.col });
		else if (currentDirection == 2)
			snake.push_back({ s.row, s.col + 1 });
		else if (currentDirection == 3)
			snake.push_back({ s.row + 1, s.col });
		else if (currentDirection == 4)
			snake.push_back({ s.row, s.col - 1 });

		Location t = snake.back();

		if (t.row < 0 || t.row >= width || t.col < 0 || t.col >= width)
			isEnd = true;
		for (int i = 0; i < snake.size(); i++) {
			if (t.row == snake[i].row && t.col == snake[i].col && i != snake.size() - 1)
				isEnd = true;
		}

		if (appleMap[t.row][t.col])
			appleMap[t.row][t.col] = false;
		else
			snake.erase(snake.begin());

		if (direction[directionIndex].second == second) {
			if (currentDirection == 1)
				currentDirection = direction[directionIndex].direction == 'D' ? 2 : 4;
			else if (currentDirection == 2)
				currentDirection = direction[directionIndex].direction == 'D' ? 3 : 1;
			else if (currentDirection == 3)
				currentDirection = direction[directionIndex].direction == 'D' ? 4 : 2;
			else
				currentDirection = direction[directionIndex].direction == 'D' ? 1 : 3;
			directionIndex++;
		}
	}

	return second;
}