#include <iostream>
using namespace std;
int main()
{
	int m = 10, n = 8, a;
	a = m-- + n++;
	cout << a << '\n';
	return 0;
}