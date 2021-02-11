#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#define MAX_NODE 2001

using namespace std;

typedef struct Road {
	int to;
	int length;
} Road;

typedef struct Node {
	vector<Road> next;
} Node;

typedef struct Queue {
	int cur;
	int length;
} Queue;

struct cmp {
	bool operator()(Queue a, Queue b) {
		return a.length < b.length;
	}
};

int n, t, s, g, h, from[3][MAX_NODE], result[101], numOfResult, gh;
Node node[MAX_NODE];

void clear() {
	for (int i = 0; i <= n; i++) 
		node[i].next.clear();
	numOfResult = 0;
	memset(from, 0, sizeof(from));
}
void dijkstra(int start, int row);
bool compare(Queue a, Queue b) {
	return a.length < b.length;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int m, tc, a, b, d;

	cin >> tc;
	for (int i = 0; i < tc; i++) {
		cin >> n >> m >> t >> s >> g >> h;
		
		for (int j = 0; j < m; j++) {
			cin >> a >> b >> d;
			node[a].next.push_back({ b, d });
			node[b].next.push_back({ a, d });
			if ((a == g && b == h) || (a == h && b == g))
				gh = d;
		}

		dijkstra(g, 1);
		dijkstra(h, 2);
		dijkstra(s, 0);

		for (int j = 0; j < t; j++) {
			cin >> d;
			if (from[1][s] < from[2][s]) {
				if (from[2][d] + gh + from[1][s] == from[0][d])
					result[numOfResult++] = d;
			}
			else if (from[1][d] + gh + from[2][s] == from[0][d])
				result[numOfResult++] = d;
		}

		sort(result, result + numOfResult);
		for (int j = 0; j < numOfResult; j++)
			cout << result[j] << " ";
		cout << "\n";

		clear();
	}
}

void dijkstra(int start, int row) {
	priority_queue<Queue, vector<Queue>, cmp> q;
	q.push({ start, 0 });

	while (!q.empty()) {
		int cur = q.top().cur, length = q.top().length;
		q.pop();

		for (int i = 0; i < node[cur].next.size(); i++) {
			Road next = node[cur].next[i];
			int* temp = &from[row][next.to];

			if ((*temp == 0 && next.to != start)|| length + next.length < *temp) {
				*temp = length + next.length;
				q.push({ next.to, *temp });
			}
		}
	}
}