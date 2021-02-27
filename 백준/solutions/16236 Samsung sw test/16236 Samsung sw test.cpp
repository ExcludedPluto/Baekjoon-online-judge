#include <iostream>
#include <list>
#define MAX_WIDTH 20

using namespace std;

typedef struct Location {
	int row;
	int col;
	int distance;
	bool operator < (Location t) {
		if (distance < t.distance)
			return true;
		else if (t.distance < distance)
			return false;
		else {
			if (row < t.row)
				return true;
			else if (t.row < row)
				return false;
			else if (col < t.col)
				return true;
			else
				return false;
		}
	}
} Location;

int map[MAX_WIDTH][MAX_WIDTH];
int width;
Location shark;

int babyShark();
bool isThereSmallThanMe(int sharkSize);

int main() {
	cin >> width;
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark.row = i;
				shark.col = j;
				shark.distance = 0;
				map[i][j] = 0;
			}
		}
	cout << babyShark();
}

int babyShark() {
	int distance = 0;
	int sharkSize = 2;
	int countEat = 0;

	while (true) {
		if (isThereSmallThanMe(sharkSize)) {
			list<Location> q;
			list<Location> canEat;
			q.push_back(shark);
			bool visit[MAX_WIDTH][MAX_WIDTH] = { 0, };
			visit[shark.row][shark.col] = true;
			while (!q.empty()) {
				Location temp = q.front();
				q.pop_front();

				if (map[temp.row][temp.col] != 0 && map[temp.row][temp.col] < sharkSize)
					canEat.push_back(temp);

				if (temp.row > 0 && !visit[temp.row - 1][temp.col] && map[temp.row - 1][temp.col] <= sharkSize) {
					q.push_back({ temp.row - 1, temp.col, temp.distance + 1 });
					visit[temp.row - 1][temp.col] = true;
				}
				if (temp.col < width - 1 && !visit[temp.row][temp.col + 1] && map[temp.row][temp.col + 1] <= sharkSize) {
					q.push_back({ temp.row, temp.col + 1, temp.distance + 1 });
					visit[temp.row][temp.col + 1] = true;
				}
				if (temp.row < width - 1 && !visit[temp.row + 1][temp.col] && map[temp.row + 1][temp.col] <= sharkSize) {
					q.push_back({ temp.row + 1, temp.col, temp.distance + 1 });
					visit[temp.row + 1][temp.col] = true;
				}
				if (temp.col > 0 && !visit[temp.row][temp.col - 1] && map[temp.row][temp.col - 1] <= sharkSize) {
					q.push_back({ temp.row, temp.col - 1, temp.distance + 1 });
					visit[temp.row][temp.col - 1] = true;
				}
			}

			//���� ������ ���� �� �԰�, visit �ʱ�ȭ, shark ��ġ, ������ Ȯ��, count 1 ����,
			if (!canEat.empty()) {
				canEat.sort();
				Location eat = canEat.front();
				map[eat.row][eat.col] = 0;
				shark.row = eat.row;
				shark.col = eat.col;
				shark.distance = 0;
				distance += eat.distance;
				countEat++;
				if (countEat == sharkSize) {
					sharkSize++;
					countEat = 0;
				}
			}
			else
				break;
		}
		else
			break;
	}

	return distance;
}

bool isThereSmallThanMe(int sharkSize) {
	for (int i = 0; i < width; i++)
		for (int j = 0; j < width; j++)
			if (map[i][j] != 0 && sharkSize > map[i][j])
				return true;
	return false;
}