#include <iostream>
using namespace std;

#define N 6

void bubble_sort(int a[], int n)
{
	int i, j, t;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1 - i; j++)
			if(a[j]>a[j+1])
			{
				t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
			}
}

int main()
{
	int a[N], i;
	cout << "������" << N << "����:" << endl;
	for (i = 0; i < N; i++)
		cin >> a[i];
	bubble_sort(a, N);
	cout << "�ź������Ϊ:" << endl;
	for (i = 0; i < N; i++)
		cout << a[i] << '\t';
	cout << endl;
	return 0;
}