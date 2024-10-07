#include <iostream>
using namespace std;
int main()
{
	int i = 1001, a = 0, b = 0, c = 0, d = 0, j = 0;
	while (i <= 9999)
	{
		d = i % 1000 % 100 % 10;
		c = int(i / 10 % 10);
		b = int(i / 100 % 10);
		a = i / 1000;
		if (a == d && c == b)
		{
			cout << i << '\t';
			j += 1;
			if (j % 6 == 0)
			{
				cout << endl;
			}
		}
		i += 1;
	}
	cout << "共" << j << "个四位逆序数" << endl;
	return 0;
}