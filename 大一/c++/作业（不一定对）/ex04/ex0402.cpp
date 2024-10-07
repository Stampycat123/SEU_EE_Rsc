#include <iostream>
using namespace std;
int main()
{
	int x, y, z;
	cout << "ÇëÊäÈëxyzµÄÖµ" << endl;
	cin >> x >> y >> z;
	if (x > y)
	{
		if (y > z)
		{
			cout << z << '\t' << y << '\t' << x << endl;
		}
		else if (x > z)
		{
			cout << y << '\t' << z << '\t' << x << endl;
		}
		else
		{
			cout << y << '\t' << x << '\t' << z << endl;
		}
	}
	else if ( x > z )
	{
		cout << z << '\t' << x << '\t' << y << endl;
	}
	    else if (y > z)  cout << x << '\t' << z << '\t' << y << endl;
		else  cout << x << '\t' << y << '\t' << z << endl;
	return 0;
}