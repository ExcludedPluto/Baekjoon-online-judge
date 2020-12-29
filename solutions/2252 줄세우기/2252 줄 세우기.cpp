#include <iostream>
#include <vector>
#include <list>
#define MAX_STUDENT 32000
using namespace std;

typedef struct Student {
	int beforeCount;
	bool isChecked;
	vector<int> next;
} Student;

Student student[MAX_STUDENT];
int numOfStudent;
int line[MAX_STUDENT];

void setLine();

int main() {
	int numOfCompare;
	cin >> numOfStudent >> numOfCompare;
	for (int i = 0; i < numOfCompare; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		student[a].next.push_back(b);
		student[b].beforeCount++;
	}

	setLine();
	for (int i = 0; i < numOfStudent; i++)
		cout << line[i] + 1 << " ";
}

void setLine() {
	list<int> q;
	for (int i = 0; i < numOfStudent; i++)
		if (student[i].beforeCount == 0) {
			q.push_back(i);
			student[i].isChecked = true;
		}

	int lineIndex = 0;
	while (!q.empty()) {
		list<int> temp;
		int length = q.size();
		//꺼내면서 줄 세우고, next로 연결될 곳 before 하나씩 지우자.
		for (int i = 0; i < length; i++) {
			int cur = q.front();
			q.pop_front();
			line[lineIndex++] = cur;
			for (int j = 0; j < student[cur].next.size(); j++) {
				student[student[cur].next[j]].beforeCount--;
				if (student[student[cur].next[j]].beforeCount == 0 && !student[student[cur].next[j]].isChecked) {
					temp.push_back(student[cur].next[j]);
					student[student[cur].next[j]].isChecked = true;
				}
			}
		}
		q = temp;
	}

	//check 안된거 그냥 하나씩 집어넣기
	for (int i = 0; i < numOfStudent; i++)
		if (!student[i].isChecked)
			line[lineIndex++] = i;
}