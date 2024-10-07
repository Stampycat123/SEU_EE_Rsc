#include <iostream>
using namespace std;

int my_strlen(char* s)
{
	int n = 0;
	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}

int main()
{
	char c[100];
	cout << "ÇëÊäÈë×Ö·û´®£º" << endl;
	cin >> c;
	char *p = c;
	cout << "×Ö·û´®³¤¶È£º" << my_strlen(p) << endl;
	return 0;
}