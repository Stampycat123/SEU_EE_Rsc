#include <iostream>
using namespace std;
int main()
{
	int k = 2, s = 0;
	while (k <= 100)
	{
		s += k;
		k += 2;
	}
	cout << "1-100中偶数和为" << s << endl;
	return 0;
}