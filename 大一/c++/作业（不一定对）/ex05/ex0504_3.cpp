#include <iostream>
using namespace std;

int gcd(int x, int y)
{
	int max = 1;
	while (x != y)
	{
		if (x > y) x -= y;
		else y -= x;
	}
	max = x;
	return max;
}

int main()
{
	int x, y;
	cin >> x >> y;
	cout << gcd(x, y) << endl;
	return 0;
}