#include <iostream>
using namespace std;

void exchange(int& a1, int& a2)
{
	int t;
	t = a1; a1 = a2; a2 = t;
}

int main()
{
	int a1, a2, a3;
	cout << "任意输入三个整数：" << endl;
	cin >> a1 >> a2 >> a3;
	if (a1 > a2)
		exchange(a1, a2);
	if (a1 > a3)
		exchange(a1, a3);
	if (a2 > a3)
		exchange(a2, a3);
	cout << "a1=" << a1 << '\t';
	cout << "a2=" << a2 << '\t';
	cout << "a3=" << a3 << '\t';
	return 0;
}