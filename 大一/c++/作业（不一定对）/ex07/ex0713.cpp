#include <iostream>
using namespace std;

void my_strcpy(char s1[], char s2[])
{
	int i;
	for (i = 0; s2[i]; i++)
	{
		s1[i] = s2[i];
	}
}

int main()
{
	char s1[128], s2[128];
	cin.getline(s1, 128);
	cin.getline(s2, 128);
	cout << s1 << endl;
	cout << s2 << endl;
	my_strcpy(s1, s2);
	cout << s1 << endl;
	cout << s2 << endl;
}