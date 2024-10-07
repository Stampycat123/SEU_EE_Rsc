#include<iostream>
#include<iomanip>
using namespace std;

#define Pi 3.141592653

class Point
{
protected:
	int x, y;
public:
	Point(int x0 = 0, int y0 = 0)
	{
		x = x0;
		y = y0;
	}

	Point(Point& p)
	{
		p.x = x;
		p.y = y;
	}

	void setPoint(int x0,int y0)
	{
		x = x0;
		y = y0;
	}

	void getPoint(int* x0, int* y0)
	{
		x0 = &x;
		y0 = &y;
	}

	void show()
	{
		cout << "(" << x << "," << y << ")" << endl;
	}
};

class Circle :public Point
{
protected:
	int radius;
public:
	Circle(int x0 = 0, int y0 = 0, int r0 = 0):Point(x0,y0)
	{
		radius = r0;
	}

	Circle(Circle& c)
	{
		c.radius = radius;
		c.x = x;
		c.y = y;
	}

	void setRadius(int r0) { radius = r0; }
	void getRadius(int& r) { r = radius; }
	double area() { return (radius * Pi * Pi); }
	void show()
	{
		cout << "圆心：(" << x << ',' << y << ')' << endl;
		cout << "半径：" << radius << endl;
		cout << "面积：" << area() << endl;
	}
};

class Cylinder :public Circle
{
protected:
	int height;
public:
	Cylinder(int x0 = 0, int y0 = 0, int r0 = 0, int h0 = 0) :Circle(x0, y0, r0)
	{
		height = h0;
	}

	Cylinder(Cylinder& Cy)
	{
		Cy.height = height;
		Cy.radius = radius;
		Cy.x = x;
		Cy.y = y;
	}

	void setHeight(int h) { height = h; }
	void getHeight(int* h) { h = &height; }
	double volumn() { return (area() * height); }
	void show()
	{
		cout << "圆心：(" << x << ',' << y << ')' << endl;
		cout << "半径：" << radius << endl;
		cout << "高度：" << height << endl;
		cout << "体积：" << volumn() << endl;
	}
};

int main()
{
	Cylinder Cy(1, 1, 1, 1);
	Cy.show();
	Cy.setHeight(2);
	Cy.show();

	return 0;
}