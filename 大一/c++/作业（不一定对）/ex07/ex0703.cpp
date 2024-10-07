#include <iostream>
using namespace std;
#include <cmath>

void input(double a[], int n)
{
	cout << "������" << n << "�����ݣ�" << endl;
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
	cout << "������100���ڵ���������n��" << endl;
	cin >> n;
	double a[100];
	if (n < 100)
	{
		input(a, n);
		cout << "��׼��Ϊ" << stddev(a, n) << endl;
	}
	else
		cout << "����100������" << endl;
	return 0;
}