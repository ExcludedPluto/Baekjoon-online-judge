#include <iostream>
#include <set>
#define MAX_N 1000

using namespace std;

typedef struct Pair {
	int value;
	int count;
	bool operator < (const Pair& p) const{
		return value < p.value;
	}
	bool operator == (const Pair&  p) const{
		return value == p.value;
	}
} Pair;

int A[MAX_N];
int B[MAX_N];
set<Pair> Bset;
int numOfA, numOfB, T;

void makeBSet();
long long getCount();

int main() {
	cin >> T >> numOfA;
	for (int i = 0; i < numOfA; i++)
		cin >> A[i];
	cin >> numOfB;
	for (int i = 0; i < numOfB; i++)
		cin >> B[i];

	makeBSet();
	cout << getCount();
}

void makeBSet() {
	for (int i = 0; i < numOfB; i++) {
		int arraySum = 0;
		for (int j = i; j < numOfB; j++) {
			arraySum += B[j];
			Pair temp = { arraySum, 1 };
			set<Pair>::iterator iter = Bset.find(temp);
			if (iter != Bset.end()) {
				temp.count += iter->count;
				Bset.erase(iter);
			}
			Bset.insert(temp);
		}
	}
}

long long getCount() {
	long long count = 0;
	for (int i = 0; i < numOfA; i++) {
		int arraySum = 0;
		for (int j = i; j < numOfA; j++) {
			arraySum += A[j];
			set<Pair>::iterator iter = Bset.find({ T - arraySum, 0 });
			if (iter != Bset.end())
				count += iter->count;
		}
	}
	return count;
}