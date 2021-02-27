#include <iostream>
#include <cstring>
#define MAX_STUDENT 100000

using namespace std;

int numOfStudent, student[MAX_STUDENT+1];
bool checkCycle[MAX_STUDENT+1];
int queue[MAX_STUDENT + 1], cycleCount;

void generateCheck();

int main() {
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		cin >> numOfStudent; 
		for (int j = 1; j <= numOfStudent; j++)
			cin >> student[j];

		cycleCount = 0;
		generateCheck();
		cout << numOfStudent - cycleCount << endl;
	}
}
void generateCheck() {
	for (int i = 1; i <= numOfStudent; i++) {
		if (student[i] != -1) {
			int start = i;
			int end = student[i];
			int index = 0;
			queue[index++] = i;
			checkCycle[start] = true;
			while (!checkCycle[end]) {
				queue[index++] = end;
				checkCycle[end] = true;
				end = student[end];
				if (end == -1)
					break;
			}

			if (start == end) {
				for(int j = 0; j<index; j++) {
					cycleCount++;
					student[queue[j]] = -1;
					checkCycle[queue[j]] = false;
				}
			}
			else {
				int j = index - 1;
				if (end != -1) {
					for (; j >= 0; j--) {
						if (queue[j] != end) {
							cycleCount++;
							student[queue[j]] = -1;
							checkCycle[queue[j]] = false;
						}
						else
							break;
					}
					cycleCount++;
				}
				for(; j>= 0; j--) {
					checkCycle[queue[j]] = false;
					student[queue[j]] = -1;
				}
			}
		}
	}
}