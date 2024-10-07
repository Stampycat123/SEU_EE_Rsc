#include <iostream>
using namespace std;

int getbits(int n)
{
	int k = 0, t = n;
	while (t)
	{
		t /= 10;
		k++;
	}
	return k;
}

void split(int a[], int n, int k)
{
	for (int i = 0; i < k; i++)
	{
		a[i] = n % 10;
		n /= 10;
	}
}

void sortd(int a[], int k)
{
	int t;
	for(int i=0;i<k;i++)
		for (int j = 0; j < k - i - 1; j++)
			if (a[j] < a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
}

void reverse(int a[], int k)
{
	int t = 0;
	for (int i = 0; i+1 <= k / 2; i++)
	{
		t = a[i];
		a[i] = a[k - i - 1];
		a[k - i - 1] = t;
	}
}

int combine(int a[],int k)
{
	int com = 0;
	for (int i = 0; i < k; i++)
	{
		com *= 10;
		com += a[i];
	}
	return com;
}

int main()
{
	int oldn = -1, n, k, a[5];
	int n1, n2;
	cout << "请输入各位数字不相同的四位或三位数:" << endl;
	cin >> n;
	k = getbits(n);
	while (n != oldn)
	{
		oldn = n;
		split(a, n, k);
		sortd(a, k);
		n1 = combine(a, k);
		reverse(a, k);
		n2 = combine(a, k);
		n = n1 - n2;
		cout << n1 << "-" << n2 << "=" << n << endl;
	}
}
//程序有bug