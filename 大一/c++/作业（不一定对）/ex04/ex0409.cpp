#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double n, Arcsh, x, u, uc;
	cout << "ÇëÊäÈëxÊôÓÚ[0.1,0.7]" << endl;
	cin >> x;
	Arcsh = 0;
	n = 1;
	u = x;
	uc = 1;
	do
	{
		Arcsh += (u*uc);
		u *= (x*x/(2*n+1));
		u *= ((2 * n - 1) / (2 * n));
		uc *= -1;
		n += 1;
	} while (fabs(u * uc) >= 1e-7);
	cout << "Arcsh(x)=" << Arcsh <<endl;
	return 0;
}