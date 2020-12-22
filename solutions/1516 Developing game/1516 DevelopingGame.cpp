#include <iostream>
#include <cstring>
#include <vector>
#define MAX_BUILDING 500

using namespace std;

typedef struct Building {
	int time;
	vector<int> next;
	int timeTaken;
	int beforeCount;
	bool isChecked;
} Building;

Building build[MAX_BUILDING];
int numOfBuilding;

void getMinTime();

int main() {
	cin >> numOfBuilding;
	memset(build, 0, sizeof(build));
	for (int i = 0; i < numOfBuilding; i++) {
		cin >> build[i].time;
		int count = 0;
		while (true) {
			int temp;
			cin >> temp;
			if (temp == -1)
				break;
			temp--;
			build[temp].next.push_back(i);
			count++;
		}
		build[i].beforeCount = count;
	}
	getMinTime();
}

void getMinTime() {
	bool check = true;
	while (check) {
		bool tempCheck = true;
		for (int i = 0; i < numOfBuilding; i++) {
			if (!build[i].isChecked && build[i].beforeCount == 0) {
				int tempTime = build[i].time + build[i].timeTaken;
				for (int j = 0; j < build[i].next.size(); j++) {
					if (build[build[i].next[j]].timeTaken < tempTime)
						build[build[i].next[j]].timeTaken = tempTime;
					build[build[i].next[j]].beforeCount--;
				}
				build[i].isChecked = true;
				tempCheck = false;
			}
		}
		if (tempCheck)
			check = false;
	}

	for (int i = 0; i < numOfBuilding; i++)
		cout << build[i].time + build[i].timeTaken << endl;
}