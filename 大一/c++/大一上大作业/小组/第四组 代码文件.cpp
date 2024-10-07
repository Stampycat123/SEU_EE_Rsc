#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<cmath>

#include <fstream>
#include <windows.h>
using namespace std;

#define N 10  //N���Ա�����Ŀ
#define W 10  //W�����������ռ���
#define T 30.0  //T%����ȷ�ȣ������ж�ԭ���ݿ��ܳ��ֵĴ���ԭ����ƫ���Ӧ������ݷ��ȴ���T%ʱ�ж�ԭ���ݿ������󣬲���ʾ


void deviation(double x[], double y[], int n, double a, double b, double dev[], double y2[])
{
	for (int i = 0; i < n; i++)
	{
		y2[i] = x[i] * a + b;
		dev[i] = y2[i] - y[i];
	}
	cout << endl;
}//����������dev�����У�������������ݴ�����y2��


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
}//�������ݼ��


double sum(double a[], int n)
{
	double s = 0;
	for (int i = 0; i < n; i++)
		s += a[i];
	return s;
}//������ͺ���


void print(double x[], int n)
{
	for (int i = 0; i < n; i++)
		cout << setw(W) << x[i];
	cout << endl;
}//�����������


void get(double x[], int n)
{
	for (int i = 0; i < N; i++)
		cin >> x[i];
}//�������뺯��


void copy(double x[], double x0[], int n)
{
	for (int i = 0; i < n; i++)
		x[i] = x0[i];
}//���鸴�ƺ���


int main()
{
	//��Ŀ���ݣ�1__9.762  2__12.719  3__15.497  4__18.143  5__18.982  6__21.008  7__24.596  8__26.285  9__29.369  10__31.17
	int choice, tp = N;  //tp�������define N����ֵ
	double x[N] = { 1,2,3,4,5,6,7,8,9,10 };
	double y[N] = { 9.762, 12.719, 15.497, 18.143, 18.982, 21.008, 24.596, 26.285, 29.369, 31.17 };
	double dev[N], y2[N];
	double wrongnum[N + 1], wrongdata[N + 1];
	double x0[N], y0[N];
loop:cout << "������ѡ��ǰ��ţ�" << endl << "1.������������" << endl << "2.����Ԥ������" << '\n';
	cin >> choice;
	if (choice == 1)
	{
		cout << "������" << tp << "���Ա���ȡֵ��" << endl;
		get(x0, N);
		cout << "�������Ӧ�����ȡֵ��" << endl;
		get(y0, N);
		copy(x, x0, N);
		copy(y, y0, N);
	}
	else if (choice == 2)
		;
	else
	{
		cout << "������Ϸ���ѡ�" << endl;
		goto loop;
	}


	double s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	s1 = sum(x, N);  //�Ա�����
	s2 = sum(y, N);  //�������
	for (int i = 0; i < 10; i++)
	{
		s3 += pow(x[i], 2);  //�Ա���ƽ����
		s4 += x[i] * y[i];  //�Ա���*�������
	}
	double a = (s4 * N - s1 * s2) / (s3 * N - pow(s1, 2));
	double b = s2 / N - a * s1 / N;


	cout << "б��    a=" << a << '\n' << "�ع�ϵ��b=" << b << endl;
	cout << endl;
	cout << "ԭ�Ա�����";
	print(x, N);
	cout << "ԭ�������";
	print(y, N);
	deviation(x, y, N, a, b, dev, y2);
	cout << "������ݣ�";
	print(y2, N);
	cout << "��Ӧ��";
	print(dev, N);
	cout << endl;


	int j = 0, bl;
	bl = inspect(wrongnum, wrongdata, y, y2, dev, j);
	if (bl)
	{
		cout << "����ԭ������";
		for (int i = 0; i < bl; i++)
		{
			cout << "��" << wrongnum[i] << "������" << wrongdata[i] << "  ";
		}
		cout << "��" << endl;
	}
	else
		cout << "û�з��ֿ��ɵ����ݡ�" << endl;


	ofstream outfile;
	outfile.open("output.csv", ios::out | ios::trunc);//����һ��.csv�ļ�
	outfile << "�Ա���" << "," << "�����" << "," << "�������" << "," << "���" << endl;
	for (int i = 0; i < N; i++)
	{
		outfile << x[i] << "," << y[i] << "," << y2[i] << "," << dev[i] << "," << endl;
	}
	outfile << "y=" << a << "x+" << b << endl;
	outfile.close();//�ر��ļ�
	//csv���


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

