#include <iostream>
#include <iomanip>
using namespace std;

struct book
{
	char bookID[20], name[20];
	double price;
};

void input(book bs[], int n)
{
	cout << "请输入n本书的价格：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> bs[i].price;
	}
}

double average(book bs[], int n)
{
	double ave = 0;
	for (int i = 0; i < n; i++)
	{
		ave += bs[i].price;
	}
	ave /= n;
	return ave;
}

int findMax(book bs[], int n)
{
	int max;
	max = 0;
	for (int i = 0; i < n; i++)
	{
		if (bs[max].price < bs[i].price)
			max = i;
	}
	return max;
}

void print(book bs[], int n)
{
	cout << setw(10) << "书号" << setw(20) << "书名" << setw(10) << "价格" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setw(10) << bs[i].bookID << setw(20) << bs[i].name << setw(10) << bs[i].price << endl;
	}
}

//void sort(book bs[], int n)
//{
//	int p = 0;
//	book t;
//	for (int i = 0; i < n - 1; i++)
//	{
//		p = i;
//		for (int j = i + 1; j < n; j++)
//		{
//			if (bs[p].price > bs[i].price)
//				p = j;
//		}
//		if (p != i)
//		{
//			t = bs[p];
//			bs[p] = bs[i];
//			bs[i] = t;
//		}
//	}
//}

void sort(book bs[], int n)
{
	int i, j;
	double p;
	for (i = 1; i < n; i++)
	{
		book b = bs[i];
		p = bs[i].price;
		for (j = i - 1; j >= 0 && p < bs[j].price; j--)
			bs[j + 1] = bs[j];
		bs[j + 1] = b;
	}
}

int main()
{
	book books[4] = { {"0101","Computer"},
		{"0102","Programming"},
		{"0103","Math"} ,
		{"0104","English"} };
	int n = 4, max;

	cout.setf(ios::left);
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);

	input(books, n);
	print(books, n);
	cout << "平均价格为" << average(books, n) << endl << endl;
	max = findMax(books, n);
	cout << "价格最高者为：" << endl;
	cout << setw(10) << books[max].bookID << setw(20) << books[max].name << setw(10) << books[max].price << endl << endl;
	sort(books, n);
	print(books, n);
	return 0;
}