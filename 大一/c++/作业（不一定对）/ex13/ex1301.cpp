#include<iostream>
#include<cmath>
using namespace std;

class Complex
{
	double real, image;
public:
	Complex(double r = 0, double i = 0) { real = r; image = i; }

	Complex operator =(const Complex& c)
	{
		real = c.real;
		image = c.image;
		return *this;
	}

	Complex operator +=(const Complex& c)
	{
		real += c.real;
		image += c.image;
		return *this;
	}

	friend Complex operator+(const Complex& c1, const Complex& c2);
	friend Complex operator+(const Complex& c, double r);
	friend Complex operator-(const Complex& c1, const Complex& c2);
	friend Complex operator-(const Complex& c, double r);
	friend Complex operator-(const Complex& c);

	void show()
	{ 
		cout << real;
		if (image > 0)
			cout << " + " << image << "i" << endl;
		else if (image < 0)
			cout << " - " << fabs(image) << "i" << endl;
		else
			cout << endl;
	}
};

Complex operator+(const Complex& c1, const Complex& c2) { return Complex(c1.real + c2.real, c1.image + c2.image); }
Complex operator+(const Complex& c, double r) { return Complex(c.real + r, c.image); }
Complex operator-(const Complex& c1, const Complex& c2) { return Complex(c1.real - c2.real, c1.image - c2.image); }
Complex operator-(const Complex& c, double r) { return Complex(c.real - r, c.image); }
Complex operator-(const Complex& c) { return Complex(-c.real, -c.image); }

int main()
{
	double r1, r2, i1, i2;
	cout << "分别输入复数1的实部和虚部：" << endl;
	cin >> r1 >> i1;
	cout << "分别输入复数2的实部和虚部：" << endl;
	cin >> r2 >> i2;
	Complex c1(r1, i1), c2(r2, i2);

	cout << "c1 = ";
	c1.show();
	cout << "c2 = ";
	c2.show();

	Complex c3;
	c3 = c1 + c2;
	cout << "c1 + c2 = ";
	c3.show();

	c3 = c1 - c2;
	cout << "c1 - c2 = ";
	c3.show();

	c3 = c1 + 5;
	cout << "c1 + 5 = ";
	c3.show();

	c3 = c2 - 8;
	cout << "c2 - 8 = ";
	c3.show();

	c3 = -c1;
	cout << "-c1 =";
	c3.show();

	c1 += c2;
	cout << "c1 += c2:c1 =";
	c1.show();

	return 0;
}