#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAX_EDGE 1000000
#define MAX_NODE 10000

using namespace std;

typedef struct Edge {
	int node1;
	int node2;
	int value;

	bool operator < (Edge e) {
		return value < e.value;
	}
} Edge;

Edge edge[MAX_EDGE];
int nodeSetNum[MAX_NODE];
vector<vector<int>> set;
int numOfNode, numOfEdge;

long long getMST();
bool unionFind(int index);

int main() {
	cin >> numOfNode >> numOfEdge;
	for (int i = 0; i < numOfEdge; i++)
		cin >> edge[i].node1 >> edge[i].node2 >> edge[i].value;
	for (int i = 0; i < numOfEdge; i++) {
		edge[i].node1;
		edge[i].node2;
	}

	cout << getMST();
}

long long getMST() {
	sort(edge, &edge[numOfEdge]);
	memset(nodeSetNum, -1, sizeof(nodeSetNum));
	long long sum = 0;
	int edgeCount = 0;
	for(int i = 0; i<numOfEdge; i++) {
		if (unionFind(i)) {
			sum += edge[i].value;
			edgeCount++;
		}
		//노드 개수 -1 이면 트리완성
		if (edgeCount == numOfNode - 1)
			break;
	}

	return sum;
}

bool unionFind(int index) {
	if (nodeSetNum[edge[index].node1] == -1 && nodeSetNum[edge[index].node2] == -1) {
		vector<int> temp;
		temp.push_back(edge[index].node1);
		temp.push_back(edge[index].node2);
		set.push_back(temp);
		nodeSetNum[edge[index].node1] = set.size() - 1;
		nodeSetNum[edge[index].node2] = set.size() - 1;
	}
	else if (nodeSetNum[edge[index].node1] == -1) {
		nodeSetNum[edge[index].node1] = nodeSetNum[edge[index].node2];
		set[nodeSetNum[edge[index].node1]].push_back(edge[index].node1);
	}
	else if (nodeSetNum[edge[index].node2] == -1) {
		nodeSetNum[edge[index].node2] = nodeSetNum[edge[index].node1];
		set[nodeSetNum[edge[index].node2]].push_back(edge[index].node2);
	}
	else if (nodeSetNum[edge[index].node1] == nodeSetNum[edge[index].node2])
		return false;
	else {
		if (nodeSetNum[edge[index].node1] < nodeSetNum[edge[index].node2]) {
			vector<int> move = set[nodeSetNum[edge[index].node2]];
			for (int i = 0; i < move.size(); i++) {
				nodeSetNum[move[i]] = nodeSetNum[edge[index].node1];
				set[nodeSetNum[edge[index].node1]].push_back(move[i]);
			}
		}
		else {
			vector<int> move = set[nodeSetNum[edge[index].node1]];
			for (int i = 0; i < move.size(); i++) {
				nodeSetNum[move[i]] = nodeSetNum[edge[index].node2];
				set[nodeSetNum[edge[index].node2]].push_back(move[i]);
			}
		}
	}
	return true;
}