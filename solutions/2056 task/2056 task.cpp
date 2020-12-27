#include <iostream>
#include <vector>
#define MAX_TASK 10000

using namespace std;

typedef struct Task {
	int time;
	int timeTaken;
	vector<int> next;
} Task;

Task task[MAX_TASK];
int numOfTask;

int minTimeComplete();

int main() {
	cin >> numOfTask;
	for (int i = 0; i < numOfTask; i++) {
		cin >> task[i].time;
		int numOfBefore;
		cin >> numOfBefore;
		for (int j = 0; j < numOfBefore; j++) {
			int before;
			cin >> before;
			task[before-1].next.push_back(i);
		}
	}

	cout << minTimeComplete();
}

int minTimeComplete() {
	int maxTime = 0;
	for (int i = 0; i < numOfTask; i++) {
		int time = task[i].time + task[i].timeTaken;
		for (int j = 0; j < task[i].next.size(); j++)
			task[task[i].next[j]].timeTaken = task[task[i].next[j]].timeTaken > time ? task[task[i].next[j]].timeTaken : time;
		maxTime = maxTime > time ? maxTime : time;
	}
	return maxTime;
}