#include <iostream>
#include <set>
#define MAX 100001

using namespace std;

int numOfGate, numOfPlane, planeCount;
bool gate[MAX];
set<int> s;

//gateIndex�� ���� �ڸ��� �ֱ�
//���� ���� �ִ��� ū ���� �ִ°� ����.
//���� 5�� ������, gateIndex���� 5�� ��ȸ�ؼ�, ����Ű�� ��ġ�� �ֱ�
//����Ű�� ��ġ�� ó���� �ڱ��ڽ�, �� �Ŀ� �־��������� 1ĭ�� ������ ����.
//��� �� �տ� �͵� ������ ����
//ex) 5 5 5 ��� ������, gateIndex�� 1 2 3 4 5 6 -> 1 2 3 4 4 6-> 1 2 3 3 3 6-> 1 2 2 2 2 6-> 1 1 1 1 1 6-> 0  0 0 0 0 6-> 0�ڸ��� ���ְ� ��. 
//1�� �ٿ��ִ°������� �ð��ʰ��� ��.
bool canPut(int max);
void makeSet();

int main() {
	cin >> numOfGate >> numOfPlane;
	makeSet();
	int temp;
	bool check = true;
	for (int i = 0; i < numOfPlane; i++) {
		cin >> temp;
		if (check && canPut(temp))
			planeCount++;
		else
			check = false;
	}
	cout << planeCount << endl;

}

void makeSet() {
	for (int i = 1; i <= numOfGate; i++)
		s.insert(i);
}

bool canPut(int max) {
	if (!gate[max]) {
		gate[max] = true;
		s.erase(s.find(max));
		return true;
	}
	else {
		set<int>::iterator iter = s.upper_bound(max);
		if (iter == s.begin())
			return false;
		else {
			iter--;
			gate[*iter] = true;
			s.erase(iter);
			return true;
		}
	}
}