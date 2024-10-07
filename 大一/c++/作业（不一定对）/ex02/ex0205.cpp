#include <iostream>
using namespace std;
int main()
{
	int a = 6, b = 7,c,d,a1,a2,a3,a4,a5,a6;
	a1 = a *= a *= b;
	cout<<"a*=a*=b: "<< a1<<'\n';
	
	a = 6;
	b = 7;
	a2 = c = b /= a;
	cout << "c=b/=a: "<<  a2<<'\n';
	
	a = 6;
	b = 7;
	a3 = a += b -= a;
	cout << "a+=b-=a: "<<  a3<<'\n';

	a = 6;
	b = 7;
	a4 = a += b += a *= b;
	cout << "a+=b+=a*=b: "<<  a4<<'\n';

	a = 6;
	b = 7;
	a5 = c = a += b += a;
	cout << "c=a+=b+=a: "<<  a5<<'\n';
	
	a = 6;
	b = 7;
	a6 = d = (c = a / b + 15);
	cout << "d=(c=a/b+15): "<< a6<<'\n';
	
	return 0;
}