#include <iostream>
using namespace std;

int main()
{
	int i, f[20] = { 1,1 }, sum = f[0] + f[1];
	for (i = 2; i < 20; i++)
	{
		f[i] = f[i - 2] + f[i - 1];
		sum += f[i];
	}
	for (i = 0; i < 20; i++)
	{
		cout << f[i] << '\t';
		if ((i + 1) % 5 == 0)
		{
			cout << '\n';
		}
	}
	cout << "前20项和为：" << sum << '\n';
	return 0;
}