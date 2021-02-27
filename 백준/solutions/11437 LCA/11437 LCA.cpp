#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NODE 50001

using namespace std;

typedef struct Node {
	int depth;
	int parent;
	vector<int> closeNode;
} Node;
Node node[MAX_NODE];		
int numOfNode, list[MAX_NODE];		
bool check[MAX_NODE];

int findLCS(int first, int second);
void makeTree(int root);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> numOfNode;
	check[1] = true;
	int temp1, temp2, numOfPair;

	for (int i = 0; i < numOfNode-1; i++) {
		cin >> temp1 >> temp2;
		if (check[temp1]) {
			node[temp2].depth = node[temp1].depth + 1;
			node[temp2].parent = temp1;
			check[temp2] = true;
			if(node[temp2].closeNode.size() > 0)
				makeTree(temp2);
		}
		else if (check[temp2]) {
			node[temp1].depth = node[temp2].depth + 1;
			node[temp1].parent = temp2;
			check[temp1] = true;
			if (node[temp1].closeNode.size() > 0)
				makeTree(temp1);
		}
		else {
			node[temp1].closeNode.push_back(temp2);
			node[temp2].closeNode.push_back(temp1);
		}
	}

	cin >> numOfPair;
	for (int i = 0; i < numOfPair; i++) {
		cin >> temp1 >> temp2;
		int curResult = node[temp1].depth < node[temp2].depth ? findLCS(temp1, temp2) : findLCS(temp2, temp1);
		cout << curResult << "\n";
	}
}

void makeTree(int root) {
	int index = 0, length = 0;
	list[length++] = root;

	while (index < length) {
		int cur = list[index++];
		int depth = node[cur].depth + 1;

		for (int i = 0; i < node[cur].closeNode.size(); i++) {
			int t = node[cur].closeNode[i];
			if (!check[t]) {
				node[t].depth = depth;
				node[t].parent = cur;
				check[t] = true;
				list[length++] = t;
			}
		}
		node[cur].closeNode.clear();
	}
	return;
}

int findLCS(int first, int second) {
	while (node[first].depth != node[second].depth)
		second = node[second].parent;
	while (first != second) {
		first = node[first].parent;
		second = node[second].parent;
	}
	return first;
}
