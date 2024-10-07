#include <iostream>
using namespace std;
int main()
{
	int m = 10, n = 8, b;
	b = m++ + ++n;
	cout << b << '\n';
	return 0;
}