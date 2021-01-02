#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define MAX_STAR 100

using namespace std;

typedef struct Star {
	double x;
	double y;
} Star;
typedef struct Distance {
	int first;
	int second;
	double distance;
	bool operator <(Distance d) {
		return distance < d.distance;
	}
} Distance;

Star star[MAX_STAR];
Distance dist[(MAX_STAR * (MAX_STAR+1))/2];
int numOfStar, checkStar[MAX_STAR], distIndex;
vector<vector<int>> set;

double getMinDistance();
void generateDistance();
bool unionFind(int a, int b);

int main() {
	cin >> numOfStar;
	for (int i = 0; i < numOfStar; i++) {
		cin >> star[i].x >> star[i].y;
	}
	for (int i = 0; i < numOfStar; i++)
		checkStar[i] = -1;

	cout.precision(20);
	cout << getMinDistance();
}

double getMinDistance() {
	generateDistance();
	sort(dist, dist + distIndex);

	double value = 0;
	int edge = 0;
	for (int i = 0; i < distIndex; i++) {
		if (unionFind(dist[i].first, dist[i].second)) {
			value += dist[i].distance;
			edge++;
		}
		if (edge == numOfStar - 1)
			break;
	}
	return value;
}

void generateDistance() {
	for (int i = 0; i < numOfStar; i++) {
		for (int j = i + 1; j < numOfStar; j++) {
			dist[distIndex].first = i;
			dist[distIndex].second = j;
			dist[distIndex++].distance = sqrt(((star[i].x - star[j].x) * (star[i].x - star[j].x)) + ((star[i].y - star[j].y) * (star[i].y - star[j].y)));
		}
	}
}

bool unionFind(int a, int b) {
	if (checkStar[a] == -1 && checkStar[b] == -1) {
		set.push_back({ a, b });
		checkStar[a] = set.size() - 1;
		checkStar[b] = set.size() - 1;
	}
	else if (checkStar[a] == -1) {
		set[checkStar[b]].push_back(a);
		checkStar[a] = checkStar[b];
	}
	else if (checkStar[b] == -1) {
		set[checkStar[a]].push_back(b);
		checkStar[b] = checkStar[a];
	}
	else if (checkStar[a] != checkStar[b]) {
		int temp = checkStar[b];
		for (int i = 0; i < set[temp].size(); i++) {
			set[checkStar[a]].push_back(set[temp][i]);
			checkStar[set[temp][i]] = checkStar[a];
		}
		set[temp].clear();
	}
	else
		return false;
	return true;
}