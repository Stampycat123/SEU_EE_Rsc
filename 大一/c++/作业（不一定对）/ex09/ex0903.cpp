#include <iostream>
using namespace std;

int main()
{
	int a[10], * p = a;
	cout << "请输入数组a的10个元素：" << endl;
	for (int i = 0; i < 10; i++)
		cin >> p[i];
	cout << "数组a：" << endl;
	for (int i = 0; i < 10; i++)
		cout << p[i] << ", ";
	
	for (int i = 0; i < 10; i++)
	{
		if (p[0] > p[i])
			p[0] = p[i];
	}
	cout << endl << "数组a中最小元素值为：" << p[0] << endl;
	return 0;
}