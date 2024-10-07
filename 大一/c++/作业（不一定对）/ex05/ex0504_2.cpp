#include <iostream>
using namespace std;

int gcd(int x, int y)
{
	int max = 1, i = 1;
	while (x != 0 && y != 0)
	{
		if (x > y)
		{
			x = x % y;
		}
		else
		{
			y = y % x;
		}
	}
	if (x == 0) max = y;
	else max = x;
	return max;
}

int main()
{
	int x, y;
	cin >> x >> y;
	cout << gcd(x, y) << endl;
	return 0;
}