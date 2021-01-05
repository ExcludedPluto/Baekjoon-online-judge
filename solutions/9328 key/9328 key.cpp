#include <iostream>
#include <cstring>
#include <list>
#include <vector>
#include <string>
#define MAX_WIDTH 102

using namespace std;

typedef struct Location {
	int row;
	int col;
} Location;

char map[MAX_WIDTH][MAX_WIDTH];
bool key[27], check[MAX_WIDTH][MAX_WIDTH];
int width, height, document;
vector<Location> closedDoor;

void getMaxDocument();
void BFSfrom(int row, int col);
bool checkCell(int row, int col);

int main() {
	int numOfTC;
	cin >> numOfTC;
	for (int i = 0; i < numOfTC; i++) {
		memset(key, false, sizeof(key));
		cin >> height >> width;
		cin.ignore();
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < width; k++)
				cin >> map[j][k];
		}
		string tempkey;
		cin >> tempkey;

		for (int j = 0; j < tempkey.length(); j++) {
			if (tempkey[j] == '0')
				break;
			key[tempkey[j] - 'a'] = true;
		}

		document = 0;
		getMaxDocument();
		cout << document << endl;
	}
}
//모든 게이트로  들어감 -> 열수 있는 문은 열고 . 로 바꾸고 안으로 들어감. 열쇠든 문서든 주으면 .으로 바꿈
	//열수 없는 문은 closedDoor에 추가
	//들어갈 수 있는 곳 BFS가 끝나면, closedDoor 검사 수행. 새로 열린 곳을 기준으로 다시 BFS 시행 열린 곳이 없으면 그때의 count 반환
void getMaxDocument() {
	//모든 게이트 검사. 게이트가 이어지는 경우 고려
	for (int i = 0; i < width; i++) {
		if (!check[0][i] && map[0][i] != '*' && checkCell(0, i)) 
			BFSfrom(0, i);
	}
	for (int i = 0; i < width; i++) {
		if (!check[height - 1][i] && map[height - 1][i] != '*' && checkCell(height - 1, i))
			BFSfrom(height - 1, i);
	}
	for (int i = 1; i < height - 1; i++) {
		if (!check[i][0] && map[i][0] != '*' && checkCell(i, 0))
			BFSfrom(i, 0);
	}
	for (int i = 1; i < height - 1; i++) {
		if (!check[i][width - 1] && map[i][width - 1] != '*' && checkCell(i, width - 1))
			BFSfrom(i, width - 1);
	}

	//closedDoor 검사 
	bool loopCheck = true;
	while (loopCheck) {
		loopCheck = false;
		int length = closedDoor.size();
		for (int i = 0; i < length; i++) {
			if (!check[closedDoor[i].row][closedDoor[i].col] && map[closedDoor[i].row][closedDoor[i].col] != '.' && key[map[closedDoor[i].row][closedDoor[i].col] - 'A']) {
				map[closedDoor[i].row][closedDoor[i].col] = '.';
				BFSfrom(closedDoor[i].row, closedDoor[i].col);
				loopCheck = true;
			}
		}
	}

	memset(check, 0, sizeof(check));
	memset(key, 0, sizeof(key));
	closedDoor.clear();
	memset(map, 0, sizeof(map));
}

void BFSfrom(int row, int col) {
	list<Location> q;
	q.push_back({ row, col });
	check[row][col] = true;

	while (!q.empty()) {
		Location temp = q.front();
		q.pop_front();

		if (temp.row > 0 && !check[temp.row - 1][temp.col] && map[temp.row - 1][temp.col] != '*') {
			if (checkCell(temp.row - 1, temp.col)) {
				check[temp.row - 1][temp.col] = true;
				q.push_back({ temp.row - 1, temp.col });
			}
		}
		if (temp.col < width - 1 && !check[temp.row][temp.col + 1] && map[temp.row][temp.col + 1] != '*') {
			if (checkCell(temp.row, temp.col + 1)) {
				check[temp.row][temp.col + 1] = true;
				q.push_back({ temp.row, temp.col + 1 });
			}
		}
		if (temp.row < height - 1 && !check[temp.row + 1][temp.col] && map[temp.row + 1][temp.col] != '*') {
			if (checkCell(temp.row + 1, temp.col)) {
				check[temp.row + 1][temp.col] = true;
				q.push_back({ temp.row + 1, temp.col });
			}
		}
		if (temp.col > 0 && !check[temp.row][temp.col - 1] && map[temp.row][temp.col - 1] != '*') {
			if (checkCell(temp.row, temp.col - 1)) {
				check[temp.row][temp.col - 1] = true;
				q.push_back({ temp.row, temp.col - 1 });
			}
		}
	}
}

bool checkCell(int row, int col) {
	if (map[row][col] == '.')
		return true;
	else if (map[row][col] == '$') {
		map[row][col] = '.';
		document++;
		return true;
	}
	else if (map[row][col] >= 'a' && map[row][col] <= 'z') {
		key[map[row][col] - 'a'] = true;
		map[row][col] = '.';
		return true;
	}
	else if(map[row][col] >= 'A' && map[row][col] <='Z'){
		if (key[map[row][col] - 'A']) {
			map[row][col] = '.';
			return true;
		}
		else {
			closedDoor.push_back({ row, col });
			return false;
		}
	}
}