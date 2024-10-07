#include <iostream>
using namespace std;

int main()
{
	int a[20] = { 1,-5,0,6,7,6,8,6,3,-5,6,5,7,-5,4,5,8,-5,4,9 };
	int i = 0, j = 0, n;
	double s1 = 0, s2 = 0;
	for (n = 0; n < 20; n++)
	{
		if (a[n] > 0)
		{
			s1 += a[n];
			i += 1;
		}
		else if (a[n] < 0)
		{
			s2 += a[n];
			j += 1;
		}
	}
	cout << "共" << i << "个正数" << endl;
	cout << "共" << j << "个负数" << endl;
	cout << "共" << 20-i-j << "个0" << endl;
	cout << "正数的平均数为" << s1 / i << endl;
	cout << "负数的平均数为" << s2 / j << endl;
}