#include <bits/stdc++.h>
#define INF 2000000000

using namespace std;

long long N, E, edges[401][401];

int floid();

int main() {
	cin >> N >> E;
	for (int i = 0; i < 401; i++)
		for (int j = 0; j < 401; j++)
			edges[i][j] = INF;
	for (int i = 0; i < E; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edges[a][b] = c;
	}

	cout << floid();
}

int floid() {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++)
				if (edges[j][k] > edges[j][i] + edges[i][k])
					edges[j][k] = edges[j][i] + edges[i][k];

	int result = INF;
	for (int i = 1; i <= N; i++)
		result = result < edges[i][i] ? result : edges[i][i];

	if (result == INF)
		return -1;
	return result;
}
