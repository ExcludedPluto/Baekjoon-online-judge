#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#define MAX_WIDTH 20
#define MAX_CUSTOMER 400
#define CUSTOMER 123

using namespace std;

typedef struct Taxi {
	int row;
	int col;
	int fuel;
} Taxi;

typedef struct Customer {
	int currentRow;
	int currentCol;
	int dstRow;
	int dstCol;
	int distance;
} Customer;

typedef struct Candidate {
	int row;
	int col;
	int fuel;
	int index;
	bool operator < (Candidate t) {
		if (fuel < t.fuel)
			return true;
		else if (fuel > t.fuel)
			return false;
		else {
			if (row < t.row)
				return true;
			else if (row > t.row)
				return false;
			else {
				if (col < t.col)
					return true;
				else
					return false;
			}
		}
	}
} Candidate;

int map[MAX_WIDTH][MAX_WIDTH];
int width, numOfCustomer;
Taxi taxi;
Customer customer[MAX_CUSTOMER];


//nxn ũ�� �ʿ� �� ĭ�� �� �Ǵ� ��ĭ
//��ĭ�� �°��� �ýð� �� �� ����
//m ���� �¿����ϰ�, m���� ���� ����� ����
//���� �ý���ġ���� ���� ����� �°��� �¿��, �������̸� ���� �۰�, ���� ���� �°� ����
//�ýÿ� �°��� ���� ��ġ�� 0, �°��� ���������� �¿����ָ�, �¿����ִ��� �Ҹ��� ������ �ι谡 ������.
//�¿�� ���߿� ���ᰡ �����Ǹ� �װɷ� ���� ����. ������ ���ÿ� ������ ������.
//�°��� �¿췯 ���� ���߿��� ����� �Ҹ�ȴ�.

int startWork();
void getCustomerDistance();
bool check();

int main() {
	cin >> width >> numOfCustomer >> taxi.fuel;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++)
			cin >> map[i][j];
	}
	cin >> taxi.row >> taxi.col;
	taxi.row--;
	taxi.col--;
	for (int i = 0; i < numOfCustomer; i++) {
		cin >> customer[i].currentRow >> customer[i].currentCol >> customer[i].dstRow >> customer[i].dstCol;
		customer[i].currentRow--;
		customer[i].currentCol--;
		customer[i].dstRow--;
		customer[i].dstCol--;
		customer[i].distance = -1;
		map[customer[i].currentRow][customer[i].currentCol] = CUSTOMER + i;
	}
	getCustomerDistance();
	if (check())
		cout << startWork();
	else
		cout << -1;
}

void getCustomerDistance() {
	for (int i = 0; i < numOfCustomer; i++) {
		bool visit[MAX_WIDTH][MAX_WIDTH] = { 0, };
		list<Taxi> q;
		vector<int> candidate;
		q.push_back({ customer[i].currentRow, customer[i].currentCol, 0 });
		visit[customer[i].currentRow][customer[i].currentCol] = true;

		while (!q.empty()) {
			Taxi temp = q.front();
			q.pop_front();

			if (temp.row == customer[i].dstRow && temp.col == customer[i].dstCol) {
				customer[i].distance = temp.fuel;
				break;
			}

			if (temp.row != 0 && map[temp.row - 1][temp.col] != 1 && !visit[temp.row - 1][temp.col]) {
				q.push_back({ temp.row - 1, temp.col, temp.fuel + 1 });
				visit[temp.row - 1][temp.col] = true;
			}
			if (temp.row != width - 1 && map[temp.row + 1][temp.col] != 1 && !visit[temp.row + 1][temp.col]) {
				q.push_back({ temp.row + 1, temp.col, temp.fuel + 1 });
				visit[temp.row + 1][temp.col] = true;
			}
			if (temp.col != 0 && map[temp.row][temp.col - 1] != 1 && !visit[temp.row][temp.col - 1]) {
				q.push_back({ temp.row, temp.col - 1, temp.fuel + 1 });
				visit[temp.row][temp.col - 1] = true;
			}
			if (temp.col != width - 1 && map[temp.row][temp.col + 1] != 1 && !visit[temp.row][temp.col + 1]) {
				q.push_back({ temp.row, temp.col + 1, temp.fuel + 1 });
				visit[temp.row][temp.col + 1] = true;
			}
		}
	}
}

bool check() {
	for (int i = 0; i < numOfCustomer; i++)
		if (customer[i].distance == -1)
			return false;
	return true;
}

int startWork() {
	for (int i = 0; i < numOfCustomer; i++) {
		//���� ����� �°� �̾Ƽ� �� ������ ����.
		Customer crtCustomer;
		int crtCustomerDistance = 0;
		if (map[taxi.row][taxi.col] >= CUSTOMER)
			crtCustomer = customer[map[taxi.row][taxi.col] - CUSTOMER];
		else {
			bool visit[MAX_WIDTH][MAX_WIDTH] = { 0, };
			visit[taxi.row][taxi.col] = true;
			list<Taxi> q;
			q.push_back({ taxi.row, taxi.col, 0 });
			vector<Candidate> candidate;

			while (!q.empty()) {
				Taxi temp = q.front();
				q.pop_front();

				if(map[temp.row][temp.col] >= CUSTOMER)
					candidate.push_back({ temp.row , temp.col, temp.fuel, map[temp.row][temp.col] - CUSTOMER });

				if (temp.row != 0 && map[temp.row - 1][temp.col] != 1 && !visit[temp.row - 1][temp.col]) {
					q.push_back({ temp.row - 1, temp.col, temp.fuel + 1 });
					visit[temp.row - 1][temp.col] = true;
				}
				if (temp.row != width - 1 && map[temp.row + 1][temp.col] != 1 && !visit[temp.row + 1][temp.col]) {
					q.push_back({ temp.row + 1, temp.col, temp.fuel + 1 });
					visit[temp.row + 1][temp.col] = true;
				}
				if (temp.col != 0 && map[temp.row][temp.col - 1] != 1 && !visit[temp.row][temp.col - 1]) {
					q.push_back({ temp.row, temp.col - 1, temp.fuel + 1 });
					visit[temp.row][temp.col - 1] = true;
				}
				if (temp.col != width - 1 && map[temp.row][temp.col + 1] != 1 && !visit[temp.row][temp.col + 1]) {
					q.push_back({ temp.row, temp.col + 1, temp.fuel + 1 });
					visit[temp.row][temp.col + 1] = true;
				}
			}
			if (candidate.size() == 0)
				return -1;
			sort(candidate.begin(), candidate.end());
			crtCustomer = customer[candidate[0].index];
			crtCustomerDistance = candidate[0].fuel;
		}

		//���� ����� �°��� ������, ���� �������, ����ϸ� �̵���Ŵ
		map[crtCustomer.currentRow][crtCustomer.currentCol] = 0;
		int distance = crtCustomer.distance + crtCustomerDistance;
		if (distance <= taxi.fuel) {
			taxi.row = crtCustomer.dstRow;
			taxi.col = crtCustomer.dstCol;
			taxi.fuel -= distance;
			taxi.fuel += (2*crtCustomer.distance);
		}
		else
			return -1;
	}

	return taxi.fuel;
}