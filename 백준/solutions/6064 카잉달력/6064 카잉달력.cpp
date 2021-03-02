#include <iostream>

using namespace std;

int M, N, x, y;

int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		cin >> M >> N >> x >> y;

		int result = 0, lap, start;

		if (M > N) {
			lap = M;
			start = x;
		}
		else if(M < N) {
			lap = N;
			start = y;
		}
		else if (x != y) {
			cout << -1 << endl;
			continue;
		}
		else {
			lap = N;
			start = y;
		}

		while (start <= M * N) {
			int t1 = start % M == 0 ? M : start % M;
			int t2 = start % N == 0 ? N : start % N;

			if (t1 == x && t2 == y) {
				result = start;
				break;
			}
			start += lap;
		}

		if (result == 0)
			cout << -1 << endl;
		else
			cout << result << endl;
	}
}