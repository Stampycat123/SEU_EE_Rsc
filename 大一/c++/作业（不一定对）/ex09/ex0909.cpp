#include <iostream>
using namespace std;

bool isLetter(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return true;
	return false;
}

char toUpper(char c)
{
	if (isLetter(c))
	{
		//对字母相关操作
		if (c >= 'a' && c <= 'z')
			c -= ('a' - 'A');
		//还可：toUpper(c);
	}
	return c;
}

void firstUpper(char* s)
{
	int p = 1;//命名成state（状态）更好
	while (*s)
	{
		if (isLetter(*s) && p)
		{
			*s = toUpper(*s);
			p = 0;
		}
		else if (!isLetter(*s))
			p = 1;
		s++;
	}
}

int main()
{
	char s[100];
	cin.getline(s, 100);
	char* ps = s;
	firstUpper(ps);
	cout << s;

	return 0;
}