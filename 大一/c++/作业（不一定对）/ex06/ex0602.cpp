#include <iostream>
using namespace std;
#include <cmath>
#define SQUARE(x) (x)*(x)
#define DIST(x1,x2,y1,y2) sqrt(SQUARE(x1-x2)+SQUARE(y1-y2))

int main()
{
	double x1, x2, y1, y2;
	cin >> x1 >> x2 >> y1 >> y2;
	cout << DIST(x1, x2, y1, y2) << endl;
	return 0;
}