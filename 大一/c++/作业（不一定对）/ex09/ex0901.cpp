#include <iostream>
using namespace std;

void exchange(int* p1, int* p2)
{
	int t;
	t = *p1; *p1 = *p2; *p2 = t;
}

int main()
{
	int a1, a2, a3;
	cout << "任意输入三个整数：" << endl;
	cin >> a1 >> a2 >> a3;
	int* p1 = &a1, * p2 = &a2, * p3 = &a3;
	if (*p1 > *p2)
		exchange(p1, p2);
	if (*p1 > *p3)
		exchange(p1, p3);
	if (*p2 > *p3)
		exchange(p2, p3);
	cout << "a1=" << *p1 << '\t';
	cout << "a2=" << *p2 << '\t';
	cout << "a3=" << *p3 << '\t';
	return 0;
}