#include <iostream>
using namespace std;

int main()
{
	double u, an, an1, t, sum;
	int n;
	u = 1;
	n = 1;
	an = 1;
	an1 = 1;
	sum = 0;
	while (n <= 20)
	{
		u = an1 / an;
		sum += u;
		t = an;
		an = an1;
		an1 += t;
		n += 1;
	}
	cout << sum << endl;
	return 0;
}