#include <iostream>
using namespace std;

#define N 4

void fsum(int a[N][N], int i, int j, int b[2])
{
	for (int k = 0; k < N; k++)
	{
		b[0] += a[i][k];
		b[1] += a[k][j];
	}
}

int main()
{
	int i, j;
	int a[N][N] = { {3,6,4,6},{8,3,1,3},{4,7,1,2},{2,9,5,3} };
	int b[2] = { 0,0 };
	cout << "请分别输入a[i][j]下标i、j" << endl;
	cin >> i >> j;
	if (i < N && j < N)
	{
		fsum(a, i - 1, j - 1, b);
		cout << "第" << i << "行之和为" << b[0] << endl << "第" << j << "列之和为" << b[1] << endl;
	}
	else
		cout << "不在数组范围内" << endl;
	return 0;
}