#include <iostream>
#include <list>

using namespace std;

list<pair<int, int>> q;
int F, G, S, U, D;
bool check[1000001];

int main() {
	cin >> F >> S >> G >> U >> D;

	q.push_back({ S, 0 });
	check[S] = true;
	bool canGo = false;
	while (!q.empty()) {
		int c = q.front().first, deep = q.front().second;
		q.pop_front();

		if (c == G) {
			cout << deep << endl;
			canGo = true;
			break;
		}
		if (c + U <= F && !check[c+U]) {
			q.push_back({ c + U, deep + 1 });
			check[c + U] = true;
		}
		if (c - D >= 1 && !check[c-D]) {
			q.push_back({ c - D, deep + 1 });
			check[c - D] = true;
		}
	}
	if (!canGo)
		cout << "use the stairs" << endl;
}
