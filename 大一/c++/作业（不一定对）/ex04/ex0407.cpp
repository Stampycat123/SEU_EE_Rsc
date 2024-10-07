#include <iostream>
using namespace std;
int main()
{
	double x, e, i;
	x = 1;
	e = 0;
	i = 1;
	while (x >= 1e-7)
	{
		e += x ;
		x /= i;
		i += 1;
	}
	cout << "e的近似值为" << e << endl;
	return 0;
}