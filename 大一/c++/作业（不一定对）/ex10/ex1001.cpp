#include<iostream>
#include<cmath>
using namespace std;

class Line
{
	int x1, y1, x2, y2;

public:
	void setPoint1(int a, int b)
	{
		x1 = a; y1 = b;
	}

	void setPoint2(int c, int d)
	{
		x2 = c; y2 = d;
	}

	void getPoint1(int* a, int* b)
	{
		*a = x1; *b = y1;
	}

	void getPoint2(int& a, int& b)
	{
		a = x2; b = y2;
	}

	void outputTwoPoint()
	{
		cout << "Point1:(" << x1 << "," << y1 << ")" << '\t';
		cout << "Point2:(" << x2 << "," << y2 << ")" << endl;
	}

	double length()
	{
		double l;
		l = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		return l;
	}
};

int main()
{
	Line L0;
	int a, b, c, d;
	cout << "��ֱ������һ��ᡢ�����꣺" << endl;
	cin >> a >> b;
	L0.setPoint1(a, b);
	cout << "��ֱ�����ڶ���ᡢ�����꣺" << endl;
	cin >> c >> d;
	L0.setPoint2(c, d);
	cout << endl;
	L0.outputTwoPoint();

	int x, y;
	L0.getPoint1(&x, &y);

	cout << "�߶εĳ���Ϊ��" << L0.length() << endl;

	return 0;
}