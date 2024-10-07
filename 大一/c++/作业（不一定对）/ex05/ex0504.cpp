#include <iostream>
using namespace std;

int gcd(int x, int y)
{
	int max = 1, i = 1;
	for (i+=1; i <= x; i+=1)
	{
		while (x%i == 0 && y%i == 0)
		{
			max *= i;
			x /= i;
			y /= i;
		}
	}
	return max;
}

int main()
{
	int x, y;
	cin >> x >> y;
	cout << gcd(x, y) <<endl;
	return 0;
}