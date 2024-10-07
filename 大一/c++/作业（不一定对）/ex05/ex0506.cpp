#include <iostream>
using namespace std;

int max3(int, int, int);

int main()
{
	int x, y, z;
	cin >> x >> y >> z;
	cout << max3(x, y, z) << endl;
	return 0;
}

int max3(int a, int b, int c)
{
	if (a >= b)
	{
		if (a >= c) return a;
		else return c;
	}
	else if (c >= b) return c;
	else return b;
}