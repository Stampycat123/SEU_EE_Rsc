#include <iostream>
using namespace std;

void printTriangle(int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= i - 1; j++)
			cout << " ";
		for (int k = 1; k <= n - i + 1; k++)
			cout << "*";
		cout << endl;
	}
}

int main()
{
	int n;
	cin >> n;
	printTriangle(n);
	return 0;
}