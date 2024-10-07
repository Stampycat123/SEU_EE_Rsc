#include <iostream>
using namespace std;

#define MIN2(x,y) (x)<(y)?(x):(y)
#define MIN4(w,x,y,z) (MIN2(w,x))<(MIN2(y,z))?(MIN2(w,x)):(MIN2(y,z))

int main()
{
	int a, b, c, d, m;
	cin >> a >> b >> c >> d;
	m = MIN4(a, b, c, d);
	cout << m << endl;
	return 0;
}