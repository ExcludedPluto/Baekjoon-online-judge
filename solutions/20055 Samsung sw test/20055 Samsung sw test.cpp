#include <iostream>
#define MAX_WIDTH 100

using namespace std;

typedef struct Cell {
	int durability;
	bool robot;
} Cell;

Cell belt[2][MAX_WIDTH];
int width, maxDurability;

int getLastSecond();
bool checkDurability();

int main() {
	cin >> width >> maxDurability;
	for (int i = 0; i < width; i++) {
		cin >> belt[0][i].durability;
		belt[0][i].robot = false;
	}
	for (int i = width - 1; i >= 0; i--) {
		cin >> belt[1][i].durability;
		belt[1][i].robot = false;
	}

	cout << getLastSecond();
}

int getLastSecond() {
	int second = 0;
	int zero = 0;
	while (true) {
		second++;
		//벨트 한칸 씩 이동
		Cell temp = belt[0][0];
		for (int i = 1; i < width; i++) {
			Cell temp2 = belt[0][i];
			belt[0][i] = temp;
			temp = temp2;
		}
		for (int i = width - 1; i >= 0; i--) {
			Cell temp2 = belt[1][i];
			belt[1][i] = temp;
			temp = temp2;
		}
		belt[0][0] = temp;
		belt[0][width - 1].robot = false;

		//로봇 이동
		for (int i = width - 2; i >= 0; i--) {
			if (belt[0][i].robot) {
				if (!belt[0][i + 1].robot && belt[0][i + 1].durability > 0) {
					belt[0][i + 1].robot = true;
					belt[0][i + 1].durability--;
					if (belt[0][i + 1].durability == 0)
						zero++;
					belt[0][i].robot = false;
				}
			}
		}
		belt[0][width - 1].robot = false;

		//로봇 올리기
		if (!belt[0][0].robot && belt[0][0].durability > 0) {
			belt[0][0].durability--;
			if (belt[0][0].durability == 0)
				zero++;
			belt[0][0].robot = true;
		}

		//체크
		if (zero >= maxDurability)
			break;
	}

	return second;
}