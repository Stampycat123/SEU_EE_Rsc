#include <iostream>
using namespace std;

void getDigits(char* s1, char* s2)
{
	while (*s1 != '\0')
	{
		if ( * s1 >= 48 &&  * s1 <= 57)
		{
			*s2 = *s1;
			s2++;
		}
		s1++;
	}
	*s2 = '\0';
}

int main()
{
	char s1[100], s2[100];
	cin.getline(s1, 100);
	char* p1 = s1, * p2 = s2;
	getDigits(p1, p2);
	for (p2 = s2; *p2 != '\0'; p2++)
	{
		cout << *p2;
	}
	cout << endl;

	return 0;
}