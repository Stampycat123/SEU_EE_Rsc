#include<iostream>
using namespace std;

class Point
{
	double x, y;
public:
	Point(double x = 0, double y = 0) { this->x = x; this->y = y; }
	void show() { cout << "( " << x << " , " << y << " )" << endl; }

	Point& operator++();
	Point& operator++(int);
	friend Point& operator--(Point& p);
	friend Point& operator--(Point& p, int);
};

Point& Point::operator++()
{
	x += 1;
	y += 1;
	return *this;
}

Point& Point::operator++(int)
{
	Point temp = *this;
	x += 1;
	y += 1;
	return temp;
}

Point& operator--(Point& p)
{
	p.x -= 1;
	p.y -= 1;
	return p;
}

Point& operator--(Point& p, int)
{
	Point temp = p;
	p.x -= 1;
	p.y -= 1;
	return temp;
}

int main()
{
	while(1)
	{
		double x0, y0;
		cout << "分别输入点的横、纵坐标，输入（0，0）以退出程序：" << endl;
		cin >> x0 >> y0;
		if (x0 == 0 || y0 == 0)
			break;
		Point p(x0, y0), p1, p2, p3, p4;
		cout << "p = ";
		p.show();
		cout << endl;

		p1 = p++;
		cout << "p++ = ";
		p1.show();
		cout << "p = ";
		p.show();
		
		cout << endl;

		p2 = p--;
		cout << "p-- = ";
		p2.show();
		cout << "p = ";
		p.show();
		
		cout << endl;

		p3 = ++p;
		cout << "++p = ";
		p3.show();
		cout << "p = ";
		p.show();
		
		cout << endl;

		p4 = --p;
		cout << "--p = ";
		p4.show();
		cout << "p = ";
		p.show();
		
		cout << endl;
	}
	cout << "程序已终止" << endl;
	return 0;
}