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
	cout << "��" << i << "������" << endl;
	cout << "��" << j << "������" << endl;
	cout << "��" << 20-i-j << "��0" << endl;
	cout << "������ƽ����Ϊ" << s1 / i << endl;
	cout << "������ƽ����Ϊ" << s2 / j << endl;
}