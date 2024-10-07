#include <iostream>
using namespace std;
int main()
{
	double x, y;
	cout << "x=" << endl;
	cin >> x;
	if (x < 1)
	{
		y = x * x;
	}
	else if (x < 10)
	{
		y = (3 * x) - 2;
	}
	     else
	     {
		     y = x * x * x - 10 * x * x + 28;
	      }

	cout << "y=" << y << endl;
	return 0;
}