#include <iostream>
using namespace std;

int hnx(int n)
{
	double output=0, x;
	cin >> x;
	if (n == 0) output = 1;
	else if (n == 1) output = (2 * x);
	else
	{
		output = 2 * x*hnx(n - 1) - 2 * (n - 1)*hnx(n - 2);
		n--;
	}
	return output;
}

int main()
{
	int n;
	cin >> n;
	cout << hnx(n) << endl;
	return 0;
}