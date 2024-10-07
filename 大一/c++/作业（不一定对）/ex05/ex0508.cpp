#include <iostream>
using namespace std;

int fib(int n)
{
	int a1 = 1, a2 = 1, t = 0;
	cout << "1" << '\t';
	if (n == 2) cout <<  "1" << endl;
	else if(n>2)
	{
		for (; n >= 2; n--)
		{   
			
			cout << a2 << '\t';
			t = a2;
			a2 += a1;
			a1 = t;
		}
	}
	cout << endl;
	return 0;
}

int main()
{
	int n;
	cin >> n;
	fib(n);
	return 0;
}