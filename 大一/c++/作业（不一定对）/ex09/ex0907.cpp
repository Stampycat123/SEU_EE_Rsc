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
	cout << "�������ַ�����" << endl;
	cin >> c;
	char *p = c;
	cout << "�ַ������ȣ�" << my_strlen(p) << endl;
	return 0;
}