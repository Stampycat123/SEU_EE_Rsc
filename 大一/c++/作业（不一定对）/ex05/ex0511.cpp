#include <iostream>
using namespace std;

void pr_rev(int x)
{
	if (x / 10 == 0 && x > 0)
	{
		cout << x;
		x /= 10;
	}
	else if (x / 10)
	{
		cout << x % 10;
		x /= 10;
		pr_rev(x);
	}
	
}

int main()
{
	int x;
	cin >> x;
	pr_rev(x);
	return 0;
}