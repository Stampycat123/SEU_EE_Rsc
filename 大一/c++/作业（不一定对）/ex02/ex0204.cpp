#include <iostream>
using namespace std;
int main()
{
	int a = 3, b = 4, c = 5,m,n,p,q;
	m = a + b > c&&b == c;
	n = a || b + c && b > c;
	p = !a || !c || b;
	q = a * b&&c + a;
	cout << "a+b>c&&b==c: " << m << '\n';
	cout << "a||b+c&&b>c: " << n << '\n';
	cout << "!a||!c||b: " << p << '\n';
	cout << "a*b&&c+a: " << q<< '\n';
	return 0;
}