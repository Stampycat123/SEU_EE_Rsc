#include <iostream>
using namespace std;
int main()
{
	int a;
	a = 7 * 2 + -3 % 5 - 4 / 3;

	float b;
	b = 510 + 3.2e3 - 5.6 / 0.03;
	cout << a << '\t' << b << endl;

	int m = 3, n = 4;
	a = m++ - - - n;
	cout << a << '\t' << m << '\t' << n << endl;
	return 0;
}