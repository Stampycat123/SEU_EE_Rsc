#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	int max(int, int);
	cout << "��������������:\n";
	cin >> a >> b;
	c = max(a, b);
	cout << "max=" << c << '\n';
	return 0;
}
int max(int x, int y)
{
	int z;
	if (x > y) z = x;
	else z = y;
	return z;
}