#include <iostream>
#include <iomanip>
using namespace std;
#define N 4
#define M 5

int sumBorder(int a[][M])
{
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		if (i == 0 || i == N - 1)
		{
			for (int j = 0; j < M; j++)
			{
				sum += a[i][j];
				cout << setw(5) << a[i][j];
			}
		}
		else
		{
			for (int j = 0; j < M; j++)
			{
				cout << setw(5) << a[i][j];
				if (j == 0 || j == M - 1)
					sum += a[i][j];
			}
		}
		cout << endl;
	}
	return sum;
}

int main()
{
	int a[N][M] = { {3,6,4,6,1},{8,3,1,3,2},{4,7,1,2,7},{2,9,5,3,3} };
	cout << "a=" << endl;
	cout << sumBorder(a) << endl;
	return 0;
}