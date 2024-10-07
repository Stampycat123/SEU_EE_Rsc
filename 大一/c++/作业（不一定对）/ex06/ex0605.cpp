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
		cout << "密码为：" << endl;
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
		cout << "原文为：" << endl;
		for (int i = 0; i < n; i++)
			cout << c[i];
	}
	return 0;
}