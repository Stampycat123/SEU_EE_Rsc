#include <iostream>
#include <math.h>
using namespace std;
int main()
{
	double a, b, c, disc, x1, x2, p, q;
	cin >> a >> b >> c;
	disc = b * b - 4 * a * c;
	p = -b / (2 * a);
	q = sqrt(disc) / (2 * a);
	x1 = p + q;
	x2 = p - q;
	cout << "x1=" << x1 << endl;
	cout << "x2=" << x2 << endl;
	return 0;
}