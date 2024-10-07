#include<iostream>
using namespace std;

#define PI 3.1415926

class Shape
{
public:
	virtual float area() = 0;
	virtual void setData(float, float = 0) = 0;
};

class Triangle :public Shape
{
	float w, h;
public:
	Triangle(float w = 0, float h = 0)
	{
		this->w = w;
		this->h = h;
	}

	float area()
	{
		return w * h / 2;
	}

	void setData(float ww, float hh = 0)
	{
		w = ww;
		h = hh;
	}
};

class Rectangle :public Shape
{
	float w, h;
public:
	Rectangle(float w = 0, float h = 0)
	{
		this->w = w;
		this->h = h;
	}

	float area()
	{
		return w * h;
	}

	void setData(float ww, float hh = 0)
	{
		w = ww;
		h = hh;
	}
};

class Square :public Shape
{
	float s;
public:
	Square(float s = 0, float none = 0)
	{
		this->s = s;
	}

	float area()
	{
		return s * s;
	}

	void setData(float ss, float none = 0)
	{
		s = ss;
	}
};

class Circle :public Shape
{
	float r;
public:
	Circle(float r = 0, float none = 0)
	{
		this->r = r;
	}

	float area()
	{
		return PI * r * r;
	}

	void setData(float R, float none = 0)
	{
		r = R;
	}
};

int main()
{
	float triW, triH, recW, recH, s, r;
	Shape* p;

//三角形
	Triangle tri;
	p = &tri;
	cout << "分别输入三角形的底和高：" << endl;
	cin >> triW >> triH;
	p->setData(triW, triH);
	cout << "三角形的面积为：" << p->area() << endl;
	cout << endl;

//矩形
	Rectangle rec;
	p = &rec;
	cout << "分别输入矩形的长和宽：" << endl;
	cin >> recW >> recH;
	p->setData(recW, recH);
	cout << "矩形的面积为：" << p->area() << endl;
	cout << endl;

//正方形
	Square squ;
	p = &squ;
	cout << "输入正方形的边长：" << endl;
	cin >> s;
	p->setData(s);
	cout << "正方形的面积为：" << p->area() << endl;
	cout << endl;

//圆
	Circle c;
	p = &c;
	cout << "输入圆的半径：" << endl;
	cin >> r;
	p->setData(r);
	cout << "圆的面积为：" << p->area() << endl;
	cout << endl;

	return 0;
}