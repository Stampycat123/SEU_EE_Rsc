#include <iostream>
using namespace std;

#define CHANGE 1

int main()
{
	char c[100];
	int n;
	cin.getline(c, 100);
	n = strlen(c);
	if (CHANGE)
	{
		cout << "����Ϊ��" << endl;
		for (int i = 0; i < n; i++)
		{
			if (c[i] != 90 && c[i] != 122)
				c[i] += 1;
			else
				c[i] -= 25;
			cout << c[i];
		}
	}
	else
	{
		cout << "ԭ��Ϊ��" << endl;
		for (int i = 0; i < n; i++)
			cout << c[i];
	}
	return 0;
}