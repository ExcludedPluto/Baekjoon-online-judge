#include <iostream>
#include <cstring>
#define MAX_WIDTH 50

using namespace std;

int map[MAX_WIDTH][MAX_WIDTH];
int tempMap[MAX_WIDTH][MAX_WIDTH];
int width, height, time;
int airCirculatorRow[2];

int airCirculator();
void diffuseDust(int row, int col);
void runAirCirculator();

int main() {
	cin >> height >> width >> time;
	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1)
				airCirculatorRow[index++] = i;
		}
	}
	cout << endl;
	cout << airCirculator();
}

int airCirculator() {
	for (int second = 0; second < time; second++) {
		for (int i = 0; i < height; i++)
			memcpy(tempMap[i], map[i], sizeof(int) * width);

		//Ȯ��
		for (int i = 0; i < height; i++) 
			for (int j = 0; j < width; j++)
				if(map[i][j] != 0)
					diffuseDust(i, j);


		for (int i = 0; i < height; i++)
			memcpy(map[i], tempMap[i], sizeof(int) * width);

		cout << endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
				cout << map[i][j] << " ";
			cout << endl;
		}
		//û����
		runAirCirculator();
	}

	int dust = 0;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			dust += map[i][j];
	return dust + 2;
}

void diffuseDust(int row, int col) {
	int count = 0;
	int dustDiffusionAmount = map[row][col] / 5;

	if (row > 0 && tempMap[row - 1][col] != -1) {
		tempMap[row - 1][col] += dustDiffusionAmount;
		count++;
	}
	if (col < width - 1) {
		tempMap[row][col + 1] += dustDiffusionAmount;
		count++;
	}
	if (row < height - 1 && tempMap[row + 1][col] != -1) {
		tempMap[row + 1][col] += dustDiffusionAmount;
		count++;
	}
	if (col > 0 && tempMap[row][col-1] != -1) {
		tempMap[row][col - 1] += dustDiffusionAmount;
		count++;
	}

	tempMap[row][col] -= (dustDiffusionAmount * count);
}

void runAirCirculator() {
	//��
	int temp = map[airCirculatorRow[0]][1];
	map[airCirculatorRow[0]][1] = 0;
	for (int i = 2; i < width; i++) {
		int temp2 = map[airCirculatorRow[0]][i];
		map[airCirculatorRow[0]][i] = temp;
		temp = temp2;
	}
	for (int i = airCirculatorRow[0]-1; i >= 0; i--) {
		int temp2 = map[i][width - 1];
		map[i][width - 1] = temp;
		temp = temp2;
	}
	for (int i = width - 2; i >= 0; i--) {
		int temp2 = map[0][i];
		map[0][i] = temp;
		temp = temp2;
	}
	for (int i = 1; i < airCirculatorRow[0]; i++) {
		int temp2 = map[i][0];
		map[i][0] = temp;
		temp = temp2;
	}

	//�Ʒ�
	temp = map[airCirculatorRow[1]][1];
	map[airCirculatorRow[1]][1] = 0;
	for (int i = 2; i < width; i++) {
		int temp2 = map[airCirculatorRow[1]][i];
		map[airCirculatorRow[1]][i] = temp;
		temp = temp2;
	}
	for (int i = airCirculatorRow[1] + 1; i < height; i++) {
		int temp2 = map[i][width - 1];
		map[i][width - 1] = temp;
		temp = temp2;
	}
	for (int i = width - 2; i >= 0; i--) {
		int temp2 = map[height - 1][i];
		map[height - 1][i] = temp;
		temp = temp2;
	}
	for (int i = height - 2; i > airCirculatorRow[1]; i--) {
		int temp2 = map[i][0];
		map[i][0] = temp;
		temp = temp2;
	}
}