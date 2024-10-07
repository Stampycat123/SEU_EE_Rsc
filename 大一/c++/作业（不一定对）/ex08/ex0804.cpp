#include <iostream>
using namespace std;

int main()
{
	int i;
	union INTCHAR
	{
		int x;
		char c[4];
	}e;
	cout << "sizeof(e)=" << sizeof(e) << endl;
	e.x = 0x12345678;
	for (i = 0; i < 4; i++)
		cout << hex << int(e.c[i]) << endl;
	cout << hex << e.x << endl;
	return 0;
}