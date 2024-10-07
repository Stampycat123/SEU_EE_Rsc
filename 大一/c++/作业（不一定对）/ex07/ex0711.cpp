#include <iostream>
using namespace std;

int main()
{
	char c[100];
	int n, dx = 0, xx = 0, sz = 0, kg = 0, qt = 0;
	cin.getline(c, 100);
	n = strlen(c);
	for (; n+1; n--)
	{
		if (c[n] >= 65 && c[n] <= 90)
			dx += 1;
		else if (c[n] >= 97 && c[n] <= 122)
			xx += 1;
		else if (c[n] >= 48 && c[n] <= 57)
			sz += 1;
		else if (c[n] == ' ')
			kg += 1;
		else
			qt += 1;
	}
	cout << "´óÐ´×ÖÄ¸£º" << dx << endl;
	cout << "Ð¡Ð´×ÖÄ¸£º" << xx << endl;
	cout << "Êý×Ö×Ö·û£º" << sz << endl;
	cout << "¿Õ¸ñ£º" << kg << endl;
	cout << "ÆäËû×Ö·û£º" << qt-1 << endl;
}