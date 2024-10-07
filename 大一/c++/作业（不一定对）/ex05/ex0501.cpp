#include <iostream>
using namespace std;

bool isprime(int x)
{
	int g = sqrt((double)x);
	for (int i = 2; i <= g; i++)
	{
		if (0 == x % i)
			return false;
	}
	return true;
}

int main()
{
	int count = 0;
	for (int v = 100; v <= 200; v++)
	{
		if (isprime(v))
		{
			cout << v << '\t';
			if (0 == ++count % 8)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
}