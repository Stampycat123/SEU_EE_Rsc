#include <iostream>
using namespace std;
int main()
{
	int k = 1, s = 0;
	while (k <= 100)
	{
		if (k % 2 == 1)
		{
			k += 1;
		}
		else
		{
			s += k;
			k += 1;
		}
	}
	cout << "1-100中偶数和为" << s << endl;
	return 0;
}