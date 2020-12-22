#include <iostream>
#include <cstring>
#include <vector>
#define MAX_CRAFT 1000

using namespace std;

typedef struct Craft {
	int time;
	int timeTaken;
	int before;
	bool isChecked;
	vector<int> next;
} Craft;

Craft craft[MAX_CRAFT];
vector<int> answer;

int main() {
	int numOfTc;
	cin >> numOfTc;
	for (int i = 0; i < numOfTc; i++) {
		memset(craft, 0, sizeof(craft));
		
		//입력
		int numOfCraft, numOfOrder, targetCraft;
		cin >> numOfCraft >> numOfOrder;
		for (int j = 0; j < numOfCraft; j++)
			cin >> craft[j].time;
		for (int j = 0; j < numOfOrder; j++) {
			int temp, temp2;
			cin >> temp >> temp2;
			temp--;
			temp2--;
			craft[temp].next.push_back(temp2);
			craft[temp2].before++;
		}
		cin >> targetCraft;
		targetCraft--;

		//계산
		bool check = true;
		while (check) {
			for (int j = 0; j < numOfCraft; j++) {
				if (!craft[j].isChecked && craft[j].before == 0) {
					int tempTime = craft[j].time + craft[j].timeTaken;
					for (int k = 0; k < craft[j].next.size(); k++) {
						if (craft[craft[j].next[k]].timeTaken < tempTime)
							craft[craft[j].next[k]].timeTaken = tempTime;
						craft[craft[j].next[k]].before--;
					}
					craft[j].isChecked = true;
					if (j == targetCraft)
						check = false;
				}
			}
		}

		answer.push_back(craft[targetCraft].time + craft[targetCraft].timeTaken);
	}
	for (int i = 0; i < answer.size(); i++)
		cout << answer[i] << endl;
}