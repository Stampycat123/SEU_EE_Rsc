#include <iostream>
using namespace std;
int main()
{
	int m, n, i = 1, j = 1;
	cout << "����������߳�m,n" << endl;
	cin >> m >> n;
	if (m >= 2 && n >= 2)
	{
		while (j <= n)
		{
			while (i <= m)
			{
				if (i == 1 || i == m)
				{
					cout << "*";
					i += 1;
				}
				else if (i > 1 && i < m)
				{
					if (j == 1||j == n)
					{
						cout << "*";
						i += 1;
					}
					else if (j > 1)
					{
						cout << " ";
						i += 1;
					}
				}
			}
			cout << endl;
			i = 1;
			j += 1;
		}
	}
	else
	{
		cout << "�޷����ɳ�����" << endl;
	}
	return 0;
}