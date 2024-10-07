#include<iostream>
#include<fstream>
using namespace std;

void exchange(int a[][4], int row1, int row2)
{
	if (row1 == row2)
		return;
	int temp[4];
	for (int i = 0; i < 4; i++)
		temp[i] = a[row1-1][i];
	for (int i = 0; i < 4; i++)
		a[row1-1][i] = a[row2-1][i];
	for (int i = 0; i < 4; i++)
		a[row2-1][i] = temp[i];
}

int main()
{
	fstream in, out;
	out.open("data.txt", ios::out);
	if (!out)
	{
		cout << "Can not open data.txt!" << endl;
		exit(3);
	}

	int a[4][4], b[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> a[i][j];
			out << a[i][j] << '\t';
		}
		out << endl;
	}

	in.open("data.txt", ios::in);
	if (!in)
	{
		cout << "Can not open data.txt!" << endl;
		exit(1);
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			in >> b[i][j];
		}

	exchange(b, 1, 3);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << b[i][j] << '\t';
		}
		cout << endl;
	}
	
	in.close();
	out.close();
	return 0;
}