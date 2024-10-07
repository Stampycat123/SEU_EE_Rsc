#include <iostream>
using namespace std;

#define N 6

void select_sort(int a[], int n)
{
	int i, j, p, t;
	for (i = 0; i < n - 1; i++)
	{
		p = i;
		for (j = i + 1; j < n; j++)
			if (a[j] < a[p])p = j;
		if(p!=i)
		{
			t = a[p]; a[p] = a[i]; a[i] = t;
		}
	}
}

int main()
{
	int a[N], i;
	cout << "请输入" << N << "个数:" << endl;
	for (i = 0; i < N; i++)
		cin >> a[i];
	select_sort(a, N);
	cout << "排好序的数为:" << endl;
	for (i = 0; i < N; i++)
		cout << a[i] << '\t';
	cout << endl;
	return 0;
}