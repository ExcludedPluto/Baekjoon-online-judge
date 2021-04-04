#include <iostream>
#include <string>

using namespace std;

string def, append;
char input[130];

void print();

int main() {
	cin.getline(input, 130);

	int i = 0;
	while (input[i] != ' ') {
		def.push_back(input[i]);
		i++;
	}

	for (; input[i] != ';'; i++) {
		if (input[i] != ',')
			append.push_back(input[i]);
		else 
			print();
	}
	print();
}

void print() {
	cout << def;
	int j = append.size() - 1;
	for (; j >= 0; j--) {
		if (append[j] == '&' || append[j] == '*')
			cout << append[j];
		else if (append[j] == ']') {
			cout << "[]";
			j--;
		}
		else
			break;
	}
	cout << " ";
	for (int k = 1; k <= j; k++) {
		if ((append[k] >= 'a' && append[k] <= 'z') || (append[k] >= 'A' && append[k] <= 'Z'))
			cout << append[k];
	}
	cout << ";" << endl;
	append.clear();
}