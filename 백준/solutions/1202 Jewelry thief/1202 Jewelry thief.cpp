#include <iostream>
#include <algorithm>
#include <set>
#define MAX 3000000

using namespace std;

typedef struct Jewelry {
	int weight;
	int value;
	bool operator < (Jewelry j) {
		if (value != j.value)
			return value > j.value;
		else
			return weight < j.weight;
	}
} Jewelry;

Jewelry jewelry[MAX];
multiset<int> bag;
int numOfJewelry, numOfBag;

long long maxValue();

int main() {
	cin >> numOfJewelry >> numOfBag;
	for (int i = 0; i < numOfJewelry; i++)
		cin >> jewelry[i].weight >> jewelry[i].value;
	for (int i = 0; i < numOfBag; i++) {
		int temp;
		cin >> temp;
		bag.insert(temp);
	}

	cout << maxValue();
}

//무게 넣어서 현재 위치 찾고, 현재 위치의 다음번 가방에 집어넣는 식
long long maxValue() {
	sort(jewelry, &jewelry[numOfJewelry]);

	long long value = 0;
	for (int i = 0; i < numOfJewelry; i++) {
		if (bag.empty())
			break;
		multiset<int>::iterator find = bag.find(jewelry[i].weight);
		if (find == bag.end()) {
			multiset<int>::iterator index = bag.insert(jewelry[i].weight);
			multiset<int>::iterator temp = bag.erase(index);
			if (temp == bag.end())
				continue;
			else
				bag.erase(temp);
		}
		else
			bag.erase(find);
		value += jewelry[i].value;
	}

	return value;
}