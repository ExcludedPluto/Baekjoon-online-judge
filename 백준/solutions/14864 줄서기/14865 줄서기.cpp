#include <iostream>

using namespace std;

int N, M, num[100001], biggerThan[100001], smallThan[100001];
bool check[100001];

bool getNum();

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a,  b;
		cin >> a >> b;
		biggerThan[a]++;
		smallThan[b]++;
	}

	if (getNum())
		for (int i = 1; i <= N; i++)
			cout << num[i] << " ";
	else 
		cout << -1 <<endl;
}

bool getNum() {
	for (int i = 1; i <= N; i++) {
		int leftSmall = i - smallThan[i]- 1;
		int cur = leftSmall + biggerThan[i] + 1;
		if (check[cur])
			return false;
		num[i] = cur;
		check[cur] = true;
	}
	return true;
}

