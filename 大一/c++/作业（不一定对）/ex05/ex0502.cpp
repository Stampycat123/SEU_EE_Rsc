#include <iostream>
using namespace std;

int fact(int n,int i)
{
	int sum = 0, t = 1;
	for (; i <= n; i++ )
	{
		sum += t *= i;
	}
	return (sum);
}

int main()
{
	int sum = 0, i = 1, n;
	cin >> n;
	cout << fact(n, i) << endl;
	return 0;
}