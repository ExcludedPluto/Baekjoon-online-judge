#include <iostream>
#include <algorithm>
#include <utility>
#include <set>
#define MAX_CARD 4000000
#define MAX_DRAW 10000

using namespace std;

int cards[MAX_CARD], draw[MAX_DRAW], numOfCard, m, numOfDraw;
bool buket[MAX_CARD + 1];
set<pair<int, int>> bound;

void buketSort();
int findCard(int drawCard);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> numOfCard >> m >> numOfDraw;
	for (int i = 0; i < m; i++) {
		int temp;
		cin >> temp;
		buket[temp] = true;
	}
	for (int i = 0; i < numOfDraw; i++) {
		cin >> draw[i];
	}
	buketSort();
	bound.insert(make_pair(0, m-1));

	for (int i = 0; i < numOfDraw; i++)
		cout << findCard(draw[i])<< "\n";
}


void buketSort() {
	int index = 0;
	for (int i = 1; i < MAX_CARD + 1; i++)
		if (buket[i]) {
			cards[index++] = i;
		}
}

int findCard(int drawCard) {

	for (set<pair<int, int>>::iterator iter = bound.begin(); iter != bound.end(); iter++) {
		if (cards[(*iter).second] > drawCard) {
			int* temp = upper_bound(cards + (*iter).first, cards + (*iter).second + 1, drawCard);
			if(temp -cards != (*iter).first)
				bound.insert(make_pair((*iter).first, temp - cards - 1));
			if(temp - cards != (*iter).second)
				bound.insert(make_pair(temp - cards + 1, (*iter).second));
			bound.erase(iter);
			return *temp;
		}
	}

}