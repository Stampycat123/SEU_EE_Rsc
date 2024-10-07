#include <iostream>
using namespace std;

int fact(int n)
{
	int t = 1;
	for (; n > 0; n--)
	{
		t *= n;
	}
	return t;
}

int com(int m, int r)
{
	int c = 1;
	c = fact(m) / (fact(r)*fact(m - r));
	return c;
}

int main()
{
	int m, n;
	cin >> m >> n;
	cout << com(m, n) << endl;
	return 0;
}