#include <iostream>
#include <iomanip>
using namespace std;

int maxValue(int a[4][4])
{
	int max = a[0][0];
	for (int* p = a[0]; p < a[0] + 16; p++)
		if (max < *p)
			max = *p;
	return max;
}

int minValue(int a[][4])
{
	int min = a[0][0];
	int(*p)[4] = a;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (min > *(*(p + i) + j))
				min = *(*(p + i) + j);
	return min;
}

double average(int(*a)[4])
{
	int sum = 0;
	double ave;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			sum += a[i][j];
	ave = sum / 16;
	return ave;
}

void print(int a[][4])
{
	int(*p)[4] = a;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << setw(5) << *(*(p + i) + j);
		cout << endl;
	}
}

int main()
{
	int a[4][4];
	int(*p)[4] = a;
	int max, min;
	double ave;
	cout << "请输入4x4的二维数组：" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cin >> *(*(p + i) + j);
		cout << endl;
	}

	print(p);
	max = maxValue(p);
	min = minValue(p);
	ave = average(p);
	cout << max << endl;
	cout << min << endl;
	cout << ave << endl;

	return 0;
}