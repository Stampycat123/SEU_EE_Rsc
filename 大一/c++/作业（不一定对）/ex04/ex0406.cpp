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
	cout << "1-100��ż����Ϊ" << s << endl;
	return 0;
}