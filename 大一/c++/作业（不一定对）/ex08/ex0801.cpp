#include <iostream>
#include <cmath>
using namespace std;

struct Point
{
	double x, y;
};

int main()
{
	Point Input();
	void Output(Point);
	double Dist(Point&, Point&);

	Point p1, p2;
	p1 = Input();
	p2 = Input();
	Output(p1);
	Output(p2);
	cout << "¾àÀëÎª£º" << Dist(p1, p2) << endl;
	return 0;
}

Point Input()
{
	Point p;
	cout << "ÇëÒÀ´ÎÊäÈëºá¡¢×Ý×ø±ê£º" << endl;
	cin >> p.x >> p.y;
	return p;
}

void Output(Point p)
{
	cout << "(" << p.x << "," << p.y << ")" << endl;
}

double Dist(Point &p1, Point &p2)
{
	double l;
	l = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	return l;
}