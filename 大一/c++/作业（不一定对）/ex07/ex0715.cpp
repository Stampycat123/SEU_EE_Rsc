#include <iostream>
using namespace std;
#define N 100
void prime(int a[], int n)
{
	int i, j;
	for (i = 1; i < n / 2; i++)
		if (a[i] != 0)
			for (j = i + 1; j < n; j++)
				if (a[j] != 0)
					if (a[j] % a[i] == 0)
						a[j] = 0;
}
int main()
{
	int a[N], i, n;
	for (i = 1;i < N; i++)
		a[i] = i + 1;
	prime(a, N);
	cout << "1~100内的素数为：" << endl;
	for (i = 1, n = 0; i < N; i++)
		if (a[i] != 0)
		{
			cout << a[i] << '\t';
			n++;
			if (n % 5 == 0)
				cout << '\n';
		}
	return 0;
}