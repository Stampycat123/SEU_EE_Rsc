#include <iostream>
using namespace std;
int main()
{
	int i = 100, a, b, c, j;
	j = i;
	while (i <= 999)
	{
		c = j % 10;
		j /= 10;
		b = j % 10;
		j /= 10;
		a = j;
		if (i == (a * a * a + b * b * b + c * c * c))
		{
			cout << i << endl;
		}
		i += 1;
		j = i;
	}
	return 0;
}