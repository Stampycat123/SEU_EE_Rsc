#include <iostream>
using namespace std;
int main()
{
	int i=0, a=1, b=0, c=0;
	while (a <= 9)
	{
		i += a * 100;
		while (b <= 9)
		{
			i += b * 10;
			while (c <= 9)
			{
				i += c;
				if (i == a * a*a + b * b*b + c * c*c)
				{
					cout << i << endl;
				}
				c += 1;
				i = a * 100 + b * 10;
			}
			b += 1;
			c = 0;
			i = a * 100;
		}
		a += 1;
		b = 0;
	}
	return 0;
}