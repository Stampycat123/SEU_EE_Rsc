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

//������
	Triangle tri;
	p = &tri;
	cout << "�ֱ����������εĵ׺͸ߣ�" << endl;
	cin >> triW >> triH;
	p->setData(triW, triH);
	cout << "�����ε����Ϊ��" << p->area() << endl;
	cout << endl;

//����
	Rectangle rec;
	p = &rec;
	cout << "�ֱ�������εĳ��Ϳ�" << endl;
	cin >> recW >> recH;
	p->setData(recW, recH);
	cout << "���ε����Ϊ��" << p->area() << endl;
	cout << endl;

//������
	Square squ;
	p = &squ;
	cout << "���������εı߳���" << endl;
	cin >> s;
	p->setData(s);
	cout << "�����ε����Ϊ��" << p->area() << endl;
	cout << endl;

//Բ
	Circle c;
	p = &c;
	cout << "����Բ�İ뾶��" << endl;
	cin >> r;
	p->setData(r);
	cout << "Բ�����Ϊ��" << p->area() << endl;
	cout << endl;

	return 0;
}