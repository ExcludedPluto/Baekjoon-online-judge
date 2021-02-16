#include <bits/stdc++.h>
#define INF 2000000000

using namespace std;

struct Line {
	int to;
	int m;
	int time;
};

vector<Line> airport[101];
int N, M, K, DP[101][10001];
queue<Line> q;

void dijkstra();
void init() {
	for (int i = 1; i <= N; i++) {
		airport[i].clear();
		for(int j = 1; j<=M; j++)
			DP[i][j] = INF;
 	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int tc;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		cin >> N >> M >> K;
		init();

		for (int j = 0; j < K; j++) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			airport[a].push_back({ b, c, d });
		}

		dijkstra();

		int answer = INF;
		for (int j = 1; j <= M; j++)
			answer = min(answer, DP[N][M]);

		if (answer == INF)
			cout << "Poor KCM" << "\n";
		else
			cout << answer << "\n";
	}
}

void dijkstra() {
	q.push({1, 0, 0});

	while (!q.empty()) {
		Line a = q.front();
		q.pop();

		if (a.time > DP[a.to][a.m])
			continue;

		for (int j = 0; j < airport[a.to].size(); j++) {
			Line next = airport[a.to][j];
			int nm = a.m + next.m, nt = a.time + next.time, to = next.to;

			if (nm <= M && nt < DP[to][nm]) {
				q.push({ to, nm, nt });
				for (int k = nm; k <= M; k++)
					if(nt < DP[to][k])
						DP[to][k] = nt;
			}
		}
	}
}