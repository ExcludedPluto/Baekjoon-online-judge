#include <iostream>
#include <set>
#define MAX 100001

using namespace std;

int numOfGate, numOfPlane, planeCount;
bool gate[MAX];
set<int> s;

//gateIndex에 넣을 자리에 넣기
//넣을 곳은 최대한 큰 곳에 넣는게 좋다.
//따라서 5가 들어오면, gateIndex에서 5를 조회해서, 가리키는 위치에 넣기
//가리키는 위치는 처음엔 자기자신, 그 후엔 넣어질때마다 1칸씩 앞으로 당기기.
//대신 그 앞에 것도 적절히 조절
//ex) 5 5 5 계속 들어오면, gateIndex는 1 2 3 4 5 6 -> 1 2 3 4 4 6-> 1 2 3 3 3 6-> 1 2 2 2 2 6-> 1 1 1 1 1 6-> 0  0 0 0 0 6-> 0자리엔 못넣게 함. 
//1씩 줄여주는과정에서 시간초과가 뜸.
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