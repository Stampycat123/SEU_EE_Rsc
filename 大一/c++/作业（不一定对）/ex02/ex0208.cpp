#include <iostream>
using namespace std;

int main()
{
	int a = 0, b = 0;float x = 0, y = 0; 
	x = a = 7.873;
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n' << '\n';
	x = 0; y = 0; a = 0; b = 0;

	a = x = 7.873;
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n' << '\n';
	x = 0; y = 0; a = 0; b = 0;

	x = a = y = 7.873;
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n' << '\n';
	x = 0; y = 0; a = 0; b = 0;

	b = x = (a = 25, 15 / 2.);
	cout << "x=" << x << '\n';
	cout << "y=" << y << '\n';
	cout << "a=" << a << '\n';
	cout << "b=" << b << '\n' << '\n';
	x = 0; y = 0; a = 0; b = 0;

	return 0;
}