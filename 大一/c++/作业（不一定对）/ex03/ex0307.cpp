#include <iostream>
using namespace std;
int main()
{
	char x = 'm', y = 'n';
	int n;
	n = x < y;
	cout << n << endl;
	n = x == y - 1;
	cout << n << endl;
	n = ('y' != 'y') + (5 > 3) + (y - x == 1);
	cout << n << endl;
	return 0;
}