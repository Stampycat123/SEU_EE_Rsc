#include <iostream>
#include <cstring>
using namespace std;

void reverse(char s[])
{
	int a;
	a = (strlen(s) + 1) / 2;
	for (int i = 0; i < a; i++)
	{
		char c = s[i];
		s[i] = s[strlen(s) - 1 - i];
		s[strlen(s) - 1 - i] = c;
	}
}

int main()
{
	char s[100];
	cin.getline(s, 100);
	reverse(s);
	cout << s << endl;
	return 0;
}