#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_PLANET 100000

using namespace std;

typedef struct Planet {
	int x;
	int y;
	int z;
} Planet;
typedef struct Distance {
	int first;
	int second;
	int distance;
	bool operator < (Distance d) {
		return distance < d.distance;
	}
} Distance;

Planet planet[MAX_PLANET];
Distance xyz[3][MAX_PLANET];
int numOfPlanet, checkPlanet[MAX_PLANET], tempXYZ[MAX_PLANET];
vector<vector<int>> set;

int abs(int a) {
	return a < 0 ? (-1) * a : a;
}
long long getMinValue();
bool putSet(int a, int b);
bool compX(int a, int b) {
	return planet[a].x < planet[b].x;
}
bool compY(int a, int b) {
	return planet[a].y < planet[b].y;
}
bool compZ(int a, int b) {
	return planet[a].z < planet[b].z;
}
void initAndSortXYZ();

int main() {
	cin >> numOfPlanet;
	for (int i = 0; i < numOfPlanet; i++)
		cin >> planet[i].x >> planet[i].y >> planet[i].z;
	for (int i = 0; i < MAX_PLANET; i++)
		checkPlanet[i] = -1;

	cout << getMinValue();
}

long long getMinValue() {
	long long value = 0;
	int Xi = 0, Yi = 0, Zi = 0, edge = 0;
	initAndSortXYZ();
	while (edge < numOfPlanet - 1) {
		int xd = xyz[0][Xi].distance, yd = xyz[1][Yi].distance, zd = xyz[2][Zi].distance;
		if (xd <= yd && xd <= zd) {
			if (putSet(xyz[0][Xi].first, xyz[0][Xi].second)) {
				value += xd;
				edge++;
			}
			Xi++;
		}
		else if (yd <= xd && yd <= zd) {
			if (putSet(xyz[1][Yi].first, xyz[1][Yi].second)) {
				value += yd;
				edge++;
			}
			Yi++;
		}
		else {
			if (putSet(xyz[2][Zi].first, xyz[2][Zi].second)) {
				value += zd;
				edge++;
			}
			Zi++;
		}
	}

	return value;
}

void initAndSortXYZ() {
	cout << endl;
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < numOfPlanet; i++)
			tempXYZ[i] = i;

		if(k == 0) sort(tempXYZ, tempXYZ + numOfPlanet, compX);
		else if(k==1)  sort(tempXYZ, tempXYZ + numOfPlanet, compY);
		else if(k==2)  sort(tempXYZ, tempXYZ + numOfPlanet, compZ);

		for (int i = 0; i < numOfPlanet - 1; i++) {
			xyz[k][i].first = tempXYZ[i];
			xyz[k][i].second = tempXYZ[i + 1];
			if (k == 0)
				xyz[k][i].distance = abs(planet[tempXYZ[i]].x - planet[tempXYZ[i + 1]].x);
			else if (k == 1)
				xyz[k][i].distance = abs(planet[tempXYZ[i]].y - planet[tempXYZ[i + 1]].y);
			else if (k == 2)
				xyz[k][i].distance = abs(planet[tempXYZ[i]].z - planet[tempXYZ[i + 1]].z);
		}
		for (int i = 0; i < numOfPlanet - 1; i++)
			cout << "( " << xyz[k][i].first << ", " << xyz[k][i].second << ", " << xyz[k][i].distance << ") ";
		sort(xyz[k], xyz[k] + numOfPlanet -1);
		for (int i = 0; i < numOfPlanet - 1; i++)
			cout << "( " << xyz[k][i].first << ", " << xyz[k][i].second << ", " << xyz[k][i].distance << ") ";
		cout << endl;
	}

	cout << endl;

}

bool putSet(int a, int b) {
	if (checkPlanet[a] == -1 && checkPlanet[b] == -1) {
		vector<int> temp;
		temp.push_back(a);
		temp.push_back(b);
		set.push_back(temp);
		checkPlanet[a] = set.size() - 1;
		checkPlanet[b] = set.size() - 1;
	}
	else if (checkPlanet[a] == -1) {
		checkPlanet[a] = checkPlanet[b];
		set[checkPlanet[b]].push_back(a);
	}
	else if (checkPlanet[b] == -1) {
		checkPlanet[b] = checkPlanet[a];
		set[checkPlanet[a]].push_back(b);
	}
	else if (checkPlanet[a] < checkPlanet[b]) {
		int temp = checkPlanet[b];
		for (int i = 0; i < set[temp].size(); i++) {
			checkPlanet[set[temp][i]] = checkPlanet[a];
			set[checkPlanet[a]].push_back(set[temp][i]);
		}
		set[temp].clear();
	}
	else if (checkPlanet[a] > checkPlanet[b]) {
		int temp = checkPlanet[a];
		for (int i = 0; i < set[temp].size(); i++) {
			checkPlanet[set[temp][i]] = checkPlanet[b];
			set[checkPlanet[b]].push_back(set[temp][i]);
		}
		set[temp].clear();
	}
	else
		return false;
	return true;
}