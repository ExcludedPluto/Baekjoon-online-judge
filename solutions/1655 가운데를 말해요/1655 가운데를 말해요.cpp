#include <iostream>
#include <set>

using namespace std;

multiset<int> s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int numOfN, temp;
	cin >> numOfN >> temp;
	s.insert(temp);
	multiset<int>::iterator middle = s.begin();
	cout << "result : " << *middle << "\n";

	for (int i = 2; i <= numOfN; i++) {
		cin >> temp;
		int cur = *middle;
		if (temp == cur)
			s.insert(s.upper_bound(temp), temp);
		else 
			s.insert(temp);

		if (i % 2 == 1) {
			if (temp >= cur)
				middle++;
		}
		else if (i % 2 == 0) {
			if (temp < cur)
				middle--;
		}
		cout << "result : " <<  *middle << "\n";
		for (multiset<int>::iterator iter = s.begin(); iter != s.end(); iter++)
			cout << *iter << " ";
		cout << "\n\n";
	}
}