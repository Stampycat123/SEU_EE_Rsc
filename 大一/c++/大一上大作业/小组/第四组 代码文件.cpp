#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include <fstream>
#include <windows.h>
using namespace std;

#define N 10  //N：自变量数目
#define W 10  //W：输出数据所占宽度
#define T 30.0  //T%：精确度，用于判断原数据可能出现的错误，原数据偏离对应拟合数据幅度大于T%时判定原数据可能有误，并提示


void deviation(double x[], double y[], int n, double a, double b, double dev[], double y2[])
{
	for (int i = 0; i < n; i++)
	{
		y2[i] = x[i] * a + b;
		dev[i] = y2[i] - y[i];
	}
	cout << endl;
}//计算离差储存在dev数组中，并计算拟合数据储存在y2中


int inspect(double wrongnum[], double wrongdata[], double y[], double y2[], double dev[], int j)
{
	for (int i = 0; i < N; i++)
	{
		if (abs(dev[i] / y2[i]) > (T / 100))
		{
			wrongnum[j] = i;
			wrongdata[j++] = y[i];
		}
	}
	return j;
}//可疑数据检查


double sum(double a[], int n)
{
	double s = 0;
	for (int i = 0; i < n; i++)
		s += a[i];
	return s;
}//数组求和函数


void print(double x[], int n)
{
	for (int i = 0; i < n; i++)
		cout << setw(W) << x[i];
	cout << endl;
}//数组输出函数


void get(double x[], int n)
{
	for (int i = 0; i < N; i++)
		cin >> x[i];
}//数组输入函数


void copy(double x[], double x0[], int n)
{
	for (int i = 0; i < n; i++)
		x[i] = x0[i];
}//数组复制函数


int main()
{
	//题目数据：1__9.762  2__12.719  3__15.497  4__18.143  5__18.982  6__21.008  7__24.596  8__26.285  9__29.369  10__31.17
	int choice, tp = N;  //tp用于输出define N的数值
	double x[N] = { 1,2,3,4,5,6,7,8,9,10 };
	double y[N] = { 9.762, 12.719, 15.497, 18.143, 18.982, 21.008, 24.596, 26.285, 29.369, 31.17 };
	double dev[N], y2[N];
	double wrongnum[N + 1], wrongdata[N + 1];
	double x0[N], y0[N];
loop:cout << "请输入选项前序号：" << endl << "1.自行输入数据" << endl << "2.采用预设数据" << '\n';
	cin >> choice;
	if (choice == 1)
	{
		cout << "请输入" << tp << "个自变量取值：" << endl;
		get(x0, N);
		cout << "请输入对应因变量取值：" << endl;
		get(y0, N);
		copy(x, x0, N);
		copy(y, y0, N);
	}
	else if (choice == 2)
		;
	else
	{
		cout << "请输入合法的选项！" << endl;
		goto loop;
	}


	double s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	s1 = sum(x, N);  //自变量和
	s2 = sum(y, N);  //因变量和
	for (int i = 0; i < 10; i++)
	{
		s3 += pow(x[i], 2);  //自变量平方和
		s4 += x[i] * y[i];  //自变量*因变量和
	}
	double a = (s4 * N - s1 * s2) / (s3 * N - pow(s1, 2));
	double b = s2 / N - a * s1 / N;


	cout << "斜率    a=" << a << '\n' << "回归系数b=" << b << endl;
	cout << endl;
	cout << "原自变量：";
	print(x, N);
	cout << "原因变量：";
	print(y, N);
	deviation(x, y, N, a, b, dev, y2);
	cout << "拟合数据：";
	print(y2, N);
	cout << "对应离差：";
	print(dev, N);
	cout << endl;


	int j = 0, bl;
	bl = inspect(wrongnum, wrongdata, y, y2, dev, j);
	if (bl)
	{
		cout << "请检查原数组中";
		for (int i = 0; i < bl; i++)
		{
			cout << "第" << wrongnum[i] << "个数据" << wrongdata[i] << "  ";
		}
		cout << "。" << endl;
	}
	else
		cout << "没有发现可疑的数据。" << endl;


	ofstream outfile;
	outfile.open("output.csv", ios::out | ios::trunc);//建立一个.csv文件
	outfile << "自变量" << "," << "因变量" << "," << "拟合数据" << "," << "离差" << endl;
	for (int i = 0; i < N; i++)
	{
		outfile << x[i] << "," << y[i] << "," << y2[i] << "," << dev[i] << "," << endl;
	}
	outfile << "y=" << a << "x+" << b << endl;
	outfile.close();//关闭文件
	//csv输出


	ShellExecute
	(
		NULL,
		L"open",
		L"output.csv",
		NULL,
		NULL,
		SW_SHOWNORMAL
	);


	return 0;
}

