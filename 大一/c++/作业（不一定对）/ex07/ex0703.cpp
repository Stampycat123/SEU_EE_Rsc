#include <iostream>
using namespace std;
#include <cmath>

void input(double a[], int n)
{
	cout << "请输入" << n << "个数据：" << endl;
	for (int i=0; i < n; i++)
	{
		cin >> a[i];
	}
}

double aver(double a[], int n)
{
	double s = 0;
	for (int i = 0; i < n; i++)
	{
		s += a[i];
	}
	return s / n;
}

double stddev(double a[], int n)
{
	double d = 0;
	for (int i = 0; i < n; i++)
	{
		d += (a[i] - aver(a, n)) * (a[i] - aver(a, n));
	}
	d = sqrt(d / n);
	return d;
}

int main()
{
	int n;
	cout << "请输入100以内的数据总数n：" << endl;
	cin >> n;
	double a[100];
	if (n < 100)
	{
		input(a, n);
		cout << "标准差为" << stddev(a, n) << endl;
	}
	else
		cout << "超出100个数据" << endl;
	return 0;
}