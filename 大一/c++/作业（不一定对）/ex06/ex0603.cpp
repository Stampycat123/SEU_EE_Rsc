#include <iostream>
using namespace std;
#include <cmath>

double square(int x)
{
	return x * x;
}

double dist(int x1, int x2, int y1, int y2)
{
	return sqrt(square(x1 - x2) + square(y1 - y2));
}

int main()
{
	double x1, x2, y1, y2;
	cin >> x1 >> x2 >> y1 >> y2;
	cout << dist(x1, x2, y1, y2) << endl;
	return 0;
}