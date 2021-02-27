#include <iostream>
#include <cstring>
#define MAX_WIDTH 20
#define MAX_COMMAND 1000

using namespace std;

typedef struct Location {
	int row;
	int col;
} Location;
typedef struct Dice {
	int top;
	int north;
	int east;
	int south;
	int western;
	int bottom;
}Dice;

int width;
int height;
int map[MAX_WIDTH][MAX_WIDTH];
Location locationDice;
int numOfCommand;
int command[MAX_COMMAND];
int dice[7];


void getProperties();
Dice diceChange(Dice d, int direction);
bool diceMove(int command);
void game();

int main() {
	getProperties();
	game();
}

void getProperties() {
	cin >> height >> width >> locationDice.row >> locationDice.col >> numOfCommand;

	for (int i = 0; i < MAX_WIDTH; i++)
		memset(map, 0, sizeof(int) * MAX_WIDTH);
	memset(dice, 0, sizeof(int) * 7);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
			cin >> map[i][j];
	}

	for (int i = 0; i < numOfCommand; i++)
		cin >> command[i];
}

void game() {
	Dice d = { 1, 2, 3, 5, 4, 6 };

	for (int i = 0; i < numOfCommand; i++) {
		if (diceMove(command[i])) {
			d = diceChange(d, command[i]);
			if (map[locationDice.row][locationDice.col] == 0)
				map[locationDice.row][locationDice.col] = dice[d.bottom];
			else {
				dice[d.bottom] = map[locationDice.row][locationDice.col];
				map[locationDice.row][locationDice.col] = 0;
			}

			cout << dice[d.top] << endl;
		}
	}
}

bool diceMove(int command) {
	//temp�� ���� �ű��, ���� ���̸� false����, �ƴϸ� ���� �� true����
	Location temp = { locationDice.row, locationDice.col };
	if (command == 1)
		temp.col++;
	else if (command == 2)
		temp.col--;
	else if (command == 3)
		temp.row--;
	else if (command == 4)
		temp.row++;

	if (temp.col < 0 || temp.col >= width || temp.row < 0 || temp.row >= height)
		return false;
	
	locationDice.col = temp.col;
	locationDice.row = temp.row;
	return true;
}

Dice diceChange(Dice d, int direction) {
	//1 : ��, 2: ��, 3: ��, 4 : ��
	Dice temp;
	if (direction == 1) {
		temp.top = d.western;
		temp.north = d.north;
		temp.east = d.top;
		temp.south = d.south;
		temp.western = d.bottom;
		temp.bottom = d.east;
	}
	else if (direction == 2) {
		temp.top = d.east;
		temp.north = d.north;
		temp.east = d.bottom;
		temp.south = d.south;
		temp.western = d.top;
		temp.bottom = d.western;
	}
	else if (direction == 3) {
		temp.top = d.south;
		temp.north = d.top;
		temp.east = d.east;
		temp.south = d.bottom;
		temp.western = d.western;
		temp.bottom = d.north;
	}
	else if (direction == 4) {
		temp.top = d.north;
		temp.north = d.bottom;
		temp.east = d.east;
		temp.south = d.top;
		temp.western = d.western;
		temp.bottom = d.south;
	}
	return temp;
}