#include <iostream>
using namespace std;
int main()
{
	double n, y, i;
	cout << "�����뾫ȷ��n" << endl;
	cin >> i;
	y = 1;
	n = 1;
	while (n <= i)
	{
		y *= (4 * n*n);
		y /= (4 * n*n - 1);
		n += 1;
	}
	cout << "Pai/2�Ľ���ֵΪ" <<2* y << endl;
	return 0;
}