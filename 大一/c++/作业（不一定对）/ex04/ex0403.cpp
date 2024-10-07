#include <iostream>
using namespace std;
int main()
{
	int x, y;
	cout << "请分别输入点A的横、纵坐标" << endl;
	cin >> x >> y;
	if (x == 0 || y == 0)
	{
		cout << 5 << endl;
	}
	else
	{
		if (x > 0)
		{
			if (y > 0)
			{
				cout << 1 << endl;
			}
			else
				cout << 4 << endl;
		}
		else
			if (y > 0)
			{
				cout << 2 << endl;
			}
			else
				cout << 3 << endl;
	}
    return 0;
}