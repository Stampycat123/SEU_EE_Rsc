#include <iostream>
using namespace std;

int main()
{
	int a[10], * p = a;
	cout << "����������a��10��Ԫ�أ�" << endl;
	for (int i = 0; i < 10; i++)
		cin >> p[i];
	cout << "����a��" << endl;
	for (int i = 0; i < 10; i++)
		cout << p[i] << ", ";
	
	for (int i = 0; i < 10; i++)
	{
		if (p[0] > p[i])
			p[0] = p[i];
	}
	cout << endl << "����a����СԪ��ֵΪ��" << p[0] << endl;
	return 0;
}