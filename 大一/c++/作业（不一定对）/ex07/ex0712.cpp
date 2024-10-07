#include <iostream>
using namespace std;

void interCross(char s1[], char s2[], char s3[])
{
	int n1, n2, n;
	n1 = strlen(s1);
	n2 = strlen(s2);
	n = n1 + n2;
	for (int i = 0; i < n; i++)
	{
		if (i % 2 == 0)
		{
			s3[i] = s1[i / 2];
			n1 -= 1;
		}
		else
		{
			s3[i] = s2[(i - 1) / 2];
			n2 -= 1;
		}
	}
}

int main()
{

	char s1[100], s2[100], s3[200];
	cin.getline(s1, 100);
	cin.getline(s2, 100);
	int n1, n2, n;
	n1 = strlen(s1);
	n2 = strlen(s2);
	n = n1 + n2;
	interCross(s1, s2, s3);
	for (int i = 0; i < n; i++)
		cout << s3[i];
}