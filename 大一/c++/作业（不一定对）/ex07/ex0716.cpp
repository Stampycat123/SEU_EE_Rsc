#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
using namespace std;

void replace(char s1[], char s2[], char s3[])
{
	int i, j;
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] == s2[0])
		{
			for (j = 1; s2[j] && s1[i + j]; j++)
			{
				if (s1[i + j] != s2[j])
					break;
			}
			if (s2[j] == 0)
			{
				int k = 0, n;
				char c[100];
				for (n = 0; n < i; n++)
				{
					c[k++] = s1[n];
				}
				for (n = 0; s3[n]; n++)
				{
					c[k++] = s3[n];
				}
				for (n = i + strlen(s2); s1[n]; n++)
				{
					c[k++] = s1[n];
				}
				c[k] = 0;
				strcpy(s1, c);
				break;
			}
		}
	}
}


int main()
{
	char s1[100] = "Today are Monday";
	char s2[100] = "are";
	char s3[100] = "is";
	cout << s1 << endl;
	replace(s1, s2, s3);
	cout << s1 << endl;
	return 0;
}
