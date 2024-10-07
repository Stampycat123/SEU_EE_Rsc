#include <iostream>
using namespace std;
int main()
{
	int a = 15, b = 18, c = 21, x, y;

	x = a < b || c++;
	cout << "x=" << x << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n';
	cout << "c=" << c << '\n' << '\n';
	a = 15; b = 18; c = 21;

	y = a > b&&c++;
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n';
	cout << "c=" << c << '\n' << '\n';
	a = 15; b = 18; c = 21;

	x = a + b > c&&c++;
	cout << "x=" << x << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n';
	cout << "c=" << c << '\n' << '\n';
	a = 15; b = 18; c = 21;

	y = a || b++ || c++;
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n';
	cout << "c=" << c << '\n' << '\n';
	return 0;
}