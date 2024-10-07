#pragma warning(disable:4996)
#include <iostream>
using namespace std;

void filter(char* p)
{
	char s[100] = { 0 }/*, * p1 = p*/;
	int i = 0/*, j = 0*/;
	while (*p != '\0')
	{
		if (isalpha(*p))
		{
			if (*p >= 97 && *p <= 122)
			{
				*p -= 32;
			}
			s[i++] = *p;
		}
		p++;
		/*j++;*/
	}
	strcpy(p, s);
	/*p = p1;
	for (int k = 0; k <= j; k++)
	{
		*p = s[k];
	}*/
}

bool palin(char* p)
{
	char s[100];
	char* head, * tail;
	strcpy(s, p);

	filter(p);
	head = p;
	tail = p;
	while (*(tail + 1) != '\0')
		tail++;
	while (head < tail)
	{
		if (*head != *tail)
			return false;
	}
	return true;
}

int main()
{
	char p[100];
	if (palin(p))
		cout << "yes" << endl;
	else
		cout << "no" << endl;

	return 0;
}