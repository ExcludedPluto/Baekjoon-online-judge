#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_STUDENT 10001

using namespace std;

int numOfStudent, numOfFriendship, money, students[MAX_STUDENT], minMoney, studentGroup[MAX_STUDENT];

void unionStudent(int first, int second);
int find(int element);
bool makeFriend();

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> numOfStudent >> numOfFriendship >> money;
	for (int i = 1; i <= numOfStudent; i++) {
		cin >> students[i];
		studentGroup[i] = i;
	}
	for (int i = 0; i < numOfFriendship; i++) {
		int first, second;
		cin >> first >> second;
		unionStudent(first, second);
	}
	if (makeFriend()) 
		cout << minMoney;
	else
		cout << "Oh no";
}

//값이 작은 게 루트에 오도록
void unionStudent(int first, int second) {
	first = find(first);
	second = find(second);

	if (students[first] <= students[second])
		studentGroup[second] = first;
	else
		studentGroup[first] = second;
}


int find(int element) {
	if (studentGroup[element] == element)
		return element;
	else
		return find(studentGroup[element]);
}

bool makeFriend() {
	for (int i = 1; i <= numOfStudent; i++) {
		if (studentGroup[i] == i) {
			if (money < students[i])
				return false;
			minMoney += students[i];
			money -= students[i];
		}
	}

	return true;
}