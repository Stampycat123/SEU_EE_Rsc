#include <iostream>
using namespace std;

void moveLeft(int* a, int n)
{
	int t = *a;
	for (int i = 0; i < n - 1; i++)
		*(a + i) = *(a + i + 1);
	*(a + n - 1) = t;
}

void rotateLeft(int* a, int n, int k)
{
	while (k)
	{
		moveLeft(a, n);
		k--;
	}
}

int main()
{
	int a[8] = { 2,3,4,5,6,7,8,9 };
	int k, n = 8, * p = a;
	cout << "����������λ��k��" << endl;
	cin >> k;
	cout << "ԭ���飺" << endl;
	for (p = a; p < a + n; p++)
		cout << *p << ", ";
	cout << endl;
	p = a;
	rotateLeft(p, n, k);
	cout << "����" << k << "λ�����飺" << endl;
	for (p = a; p < a + n; p++)
		cout << *p << ", ";
	cout << endl;
	return 0;
}