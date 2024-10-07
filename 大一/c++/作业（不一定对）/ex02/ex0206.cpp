#include <iostream>
using namespace std;
int main()
{
	int a = 5, b = 8, c = 9, x, y, z;
	y = (a + b, c + a);
	cout << "y=" << y << '\n' << '\n';

	y = (x = a * b, x + x, x*x);
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n' << '\n';

	x = y = a;
	z = a + b;
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "z=" << z << '\n' << '\n';

	x = (y = a, z = a + b);
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "z=" << z << '\n' << '\n';
	return 0;
}