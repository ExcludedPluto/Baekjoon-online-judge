#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAX_WAY 1000000
#define MAX_NODE 100000

using namespace std;

typedef struct Way {
	int node1;
	int node2;
	int value;
	bool operator < (Way w) {
		return value < w.value;
	}
} Way;

Way way[MAX_WAY];
int node[MAX_NODE+1];

vector<vector<int>> set;
vector<int> MST;
int numOfWay, numOfHouse;

int getMinValue();
void makeMST();

int main() {
	cin >> numOfHouse >> numOfWay;
	for (int i = 0; i < numOfWay; i++)
		cin >> way[i].node1 >> way[i].node2 >> way[i].value;

	cout << getMinValue();
}

int getMinValue() {
	sort(way, &way[numOfWay]);
	memset(node, -1, sizeof(node));
	makeMST();

	sort(MST.begin(), MST.end());
	MST.pop_back();
	int value = 0;
	for (int i = 0; i < MST.size(); i++)
		value += way[MST[i]].value;
	return value;
}

void makeMST() {
	for (int i = 0; i < numOfWay; i++) {
		if (node[way[i].node1] == -1 && node[way[i].node2] == -1) {
			vector<int> temp;
			temp.push_back(i);
			set.push_back(temp);
			node[way[i].node1] = set.size() - 1;
			node[way[i].node2] = set.size() - 1;
		}
		else if (node[way[i].node1] == -1) {
			node[way[i].node1] = node[way[i].node2];
			set[node[way[i].node1]].push_back(i);
		}
		else if (node[way[i].node2] == -1) {
			node[way[i].node2] = node[way[i].node1];
			set[node[way[i].node2]].push_back(i);
		}
		else {
			if (node[way[i].node1] < node[way[i].node2]) {
				int temp = node[way[i].node2];
				for (int j = 0; j < set[temp].size(); j++) {
					node[way[set[temp][j]].node1] = node[way[i].node1];
					node[way[set[temp][j]].node2] = node[way[i].node1];
					set[node[way[i].node1]].push_back(set[temp][j]);
				}
				set[node[way[i].node1]].push_back(i);
				set[temp].clear();
			}
			else if (node[way[i].node1] > node[way[i].node2]) {
				int temp = node[way[i].node1];
				for (int j = 0; j < set[temp].size(); j++) {
					node[way[set[temp][j]].node1] = node[way[i].node2];
					node[way[set[temp][j]].node2] = node[way[i].node2];
					set[node[way[i].node2]].push_back(set[temp][j]);
				}
				set[node[way[i].node1]].push_back(i);
				set[temp].clear();
			}
		}

	}
	MST = set[0];
	set.clear();
}