#include <iostream>
#include <string.h>
using namespace std;

void swap(char* p1, char* p2)
{
	char* t;
	*t = *p1; *p1 = *p2; *p2 = *t;
}

int main()
{
	char str1[64], str2[64], str3[64];
	cin >> str1 >> str2 >> str3;
	char* p1 = str1, * p2 = str2, * p3 = str3;
	swap(p1, p2);
	cout << str1;
}