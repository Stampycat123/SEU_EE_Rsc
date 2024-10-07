#include <iostream>
using namespace std;

void output(int a[], int n)
{
	cout << "数组a：";
	for (int i = 0; i < n; i++)
		cout << a[i] << "  ";
}

int deleteElement(int a[],int n,int x)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == x)
		{
			n--;
			for (int j = i; j < n; j++)
			{
				a[j] = a[j + 1];
			}
			a[n] = 0;
		}
	}
	return n;
}

int main()
{
	int n, x;
	int a[6] = { 9,5,6,7,8,5 };
	n = 6;
	output(a, n);
	cout << "请输入删除的元素：" << endl;
	cin >> x;
	cout << "数组a余" << deleteElement(a, n, x) << "个元素" << endl;
	output(a, n);
	return 0;
}