#include <iostream>
using namespace std;

#define N 4
#define M 5

int sumBorder(int a[][M])
{
	int sum = 0;
	for (int i = 1; i < N - 1; i++)
	{
		for (int j = 1; j < M - 1; j++)
		{
			sum += a[i][j];
		}
	}
	return sum;
}

int main()
{
	int sum = 0;
	cout << "a=" << endl;
	int a[N][M] = { {3,6,4,6,1},{8,3,1,3,2},{4,7,1,2,7},{2,9,5,3,3} };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			sum += a[i][j];
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
	cout << sum - sumBorder(a) << endl;
	return 0;
}