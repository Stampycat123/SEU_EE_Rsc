#include <iostream>
using namespace std;
int main()
{
	int x = 1, y = 3, z = 5;
	
	x += y *= z -= 2;
	cout << x << '\t' << y << '\t' << z << endl;
	x *= y /= z -= x;
	cout << x << '\t' << y << '\t' << z << endl;
	x = y = z = 2;
	z = (x *= 2) + (y += 4) + 2;
	cout << z << endl;
	cout << x << '\t' << y << '\t' << z << endl;
	return 0;
}