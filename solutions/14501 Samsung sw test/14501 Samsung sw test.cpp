#include <iostream>
#define MAX_DAY 15

using namespace std;

int day;
int time[MAX_DAY];
int proceeds[MAX_DAY];

int DP(int d, int proceed);
int max(int a, int b);

int main() {
	cin >> day;
	for (int i = 0; i < day; i++)
		cin >> time[i] >> proceeds[i];

	cout << DP(0, 0);
 }

int DP(int d, int proceed) {
	if (d >= day)
		return proceed;
	
	int a = 0;
	if (day - d >= time[d])
		a = DP(d + time[d], proceed + proceeds[d]);
	return max(a, DP(d + 1, proceed));
}

int max(int a, int b) {
	return a > b ? a : b;
}