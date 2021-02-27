#include <bits/stdc++.h>

using namespace std;

int N, M, K, length, DP[101][101][81];
char board[101][101], keyword[81];

int generateDFS();
int DFS(int, int, int);

int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> board[i][j];
	string t;
	cin >> t;
	for (int i = 0; i < t.size(); i++)
		keyword[i] = t[i];
	length = t.size();

	cout << generateDFS();
}

int generateDFS() {
	int result = 0;
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < M; j++) 
			if (board[i][j] == keyword[0])
				result += DFS(i, j, 0);
	return result;
}

int DFS(int r, int c, int d) {
	if (d == length - 1)
		return 1;
	if (DP[r][c][d] != 0)
		return DP[r][c][d];

	int result = 0;
	for (int i = 1; i <= K; i++) {
		if (r - i >= 0 && board[r - i][c] == keyword[d + 1])
			result += DFS(r - i, c, d + 1);
		if (r + i <= N - 1 && board[r + i][c] == keyword[d + 1])
			result += DFS(r + i, c, d + 1);
		if (c - i >= 0 && board[r][c - i] == keyword[d + 1])
			result += DFS(r, c - i, d + 1);
		if (c + i <= M - 1 && board[r][c + i] == keyword[d + 1])
			result += DFS(r, c + i, d + 1);
	}
	return DP[r][c][d] = result;
}