#include <iostream>
using namespace std;
int main()
{
	int m, n, i = 1, j = 1;
	cout << "����������߳�m,n" << endl;
	cin >> m >> n;
	if (m >= 2 && n >= 2)
	{
		while (j<=n)
		{
			if (j == 1)
			{
				while (i <= m)
				{
					cout << "*";
					i += 1;
				}
				cout << endl;
				i = 1;
				j += 1;
			}
			else if (j < n)
			{
				while (j < n)
				{
					cout << "*";
					i += 2;
					while (i <= m)
					{
						cout << " ";
						i += 1;
					}
					cout << "*";
					cout << endl;
					i = 1;
					j += 1;
				}
				
			}
			else if (j == n)
			{
				while (i <= m)
				{
					cout << "*";
					i += 1;
				}
				cout << endl;
				i = 1;
				j += 1;
			}
		}
	}
	else
	{
		cout << "�޷����ɳ�����" << endl;
	}
	return 0;
}