#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Fraction
{
	//这个类中所有的构造、析构请答题者自行建构
	//（50分）
private:
	//填充必要的成员变量
	int n;	//	代表分子
	int m;	//  代表分母

	//如还要需要其他成员变量，请自行补充



public:
	//填充必要的成员函数
	void HuaJian()
	{
		int i;
		for (i = (m < n ? m : n); i >= 1; i--)
			if (m % i == 0 && n % i == 0)
				break;
		m /= i;
		n /= i;
	}
	//单参数构造，输入分子，分母置 1
	Fraction(int a             /* 参数请自行填写 */)
	{
		//内容请自行填写
		n = a;
		m = 1;
	}

	//双参数构造，输入分子、分母
	Fraction(int a,int b                                /* 参数请自行填写 */)
	{
		//内容请自行填写
		m = b;
		n = a;
	}


	//AddWith
	void AddWith(Fraction item                       /* 参数请自行补充 */)
	{
		//内容请自行补充
		int newm = m, newn = n;
		newm *= item.m;
		newn *= item.n;
		item.m *= m;
		item.n *= m;
		newn += item.n;
		m = newm;
		n = newn;


	}

	//MulWith
	void MulWith(  Fraction &item                       /* 参数请自行补充 */)
	{
		//内容请自行补充
		m *= item.m;
		n *= item.n;


	}
	

	void Print() const
	{
		//内容请自行补充
		int i;
		for (i = (m < n ? m : n); i >= 1; i--)
			if (m % i == 0 && n % i == 0)
				break;
		int a = m, b = n;
		a /= i;
		b /= i;
		if(a>0)
		{
			if (a != 1)
				cout << "最简分数： " << b << " / " << a << endl;
			else
				cout << "最简分数： " << b << endl;
		}
		else if (a < 0)
		{
			cout << "最简分数： " << (-1) * b << " / " << (-1) * a << endl;
		}

	}


	//如果还需要增加其他成员函数，请自行补充

};

//构建一个Fraction 分数类，完成分数的计算，
//所有的数据都必须以分数，即"a / b"的形式输出，如果b为1，则只输出a
//并且注意， a/b 是约分后的结果

int main()
{
	//输出 1 + (1/2)*(1/2) + (1/3)*(1/3) + ... + (1/10)(1/10) 的结果 
	//以分数形式输出
	Fraction sum(0);			// sum = 0，即 0/1，这里调用了单参数构造
	for (int i = 1; i <= 10; ++i)
	{
		Fraction item(1, i);	// 实现 item = 1/i
		item.MulWith(item);		// 实现 item = item * item
		sum.AddWith(item);		// 实现 sum += item
	}

	sum.Print();
}




