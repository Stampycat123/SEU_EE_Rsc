#include <iostream>
using namespace std;

int fsum(int a, int b)
{
	return (a + b);
}

int fsum(int a, int b,int c)
{
	return (a + b + c);
}

double fsum(double a, double b)
{
	return (a + b);
}

double fsum(double a, double b,double c)
{
	return (a + b + c);
}

int main()
{
	int a1, a2, a3;
	double b1, b2, b3;
	cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
	cout << fsum(a1, a2) << '\t' << fsum(a1, a2, a3) << '\t' << fsum(b1, b2) << '\t' << fsum(b1, b2, b3) << endl;
	return 0;
}
