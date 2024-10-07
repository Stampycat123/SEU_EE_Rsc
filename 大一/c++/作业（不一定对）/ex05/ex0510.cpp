#include <iostream>
using namespace std;

void printTriangle(int n)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (j <= i)
			{
				cout << " ";
			}
			else
			{
				cout << "*";
			}
		}
		cout << endl;
	}
}

int main()
{
	int a;
	cin >> a;
	printTriangle(a);
	return 0;
}