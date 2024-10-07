#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

#define MAX_ERROR 0.0000001          // 前后两次高斯牛顿迭代之间的阈值

// 多项式方程求解器，支持通过构造函数设置初值，通过GetRoot()函数求根
// 注意：F(), Diff() 表示函数，以及导数
class FunctionResolver
{
private:
	double initValue;	//迭代初始值
	double* arr;
	int arrSize;

public:
	FunctionResolver(double* coefficients, int coefficientCount,
		double initValue = 0) :initValue(initValue)
	{
		arrSize = coefficientCount;
		arr = new double[arrSize];
		for (int i = 0; i < coefficientCount; ++i)
			arr[i] = coefficients[i];
	}

	virtual ~FunctionResolver()
	{
		delete[]arr;
	}

public:
	double F(const double x) const
	{
		// 按照题中表1，利用arr和arrSize，输出函数在x处的值

		double sum = 0;
		double pi_ = 1;

		for (int i = 0; i < arrSize; ++i)
		{
			double coef = arr[i];
			// 请填写代码------------8分-------------------
			sum += coef * pow(x, i);
		}
		return sum;
	}

	virtual double Diff(const double x) const
	{
		// 按照题中表1，利用arr和arrSize，输出函数在x处的导数
		// 请填写代码------------12分-------------------
		double sum = 0;
		double* arrDF = new double[arrSize];

		for (int i = 0; i < arrSize; ++i)
		{
			if (i == 0)
				arrDF[i] = 0;
			else
				arrDF[i] = arr[i] * i;
		}//求导后系数

		for (int i = 0; i < arrSize; ++i)
		{
			double coef = arrDF[i];
			if (i == 0)
				sum += 0;
			else
				sum += coef * pow(x, i - 1);
		}
		
		return sum;
	}

	double GetRoot() const
	{

		double xn = initValue;
		double xn_old;				//如有必要，可自行初始化

		// 高斯牛顿迭代法的迭代过程代码书写 （利用两次迭代 x
		// 插值小于MAX_ERROR(即0.0000001）时，则退出迭代）
		// 为了展示迭代过程，请打印每次迭代出的根值	
		// 请填写代码------------10分-------------------
		double f, f1;
		int i = 0;
		do
		{
			xn_old = xn;
			f = F(xn);
			f1 = Diff(xn);
			xn = xn_old - f / f1;

			i++;
			cout << "第" << i << "次迭代后x:\t" << setprecision(10) << xn << endl;
		} while (fabs(xn - xn_old) >= MAX_ERROR);

		return xn;
	}
};


int main()
{
	// 填空4： 补充代码，求 f(x) = 4 - x + 5 x**2 + x**3 在-1附近和x轴的交点 
	cout << "为便于观察，已将浮点数输出精度设为10" << endl;
	cout << "------------------------------------------------------" << endl;
	double cofs[4] = { 4, -1, 5, 1 };
	FunctionResolver fr(cofs, 4, -1);

	double root = fr.GetRoot();

	cout << "方程的解为：" << root << endl;
}


// 回答问题（5分）：如果要设计一个通用方程求解器，
// 适合更多的方程，你会如何考虑？利用本学年所学，说说你的设想。

//答：
//1.采用cin.getline函数进行输入，以字符串形式利用char*储存输入的函数；限定一定字符的使用；
//2.利用switch case函数与ascii，对输入的字符进行遍历，分类为各种运算符并利用数组记录各种运算符的下标；
//3.通过下标访问某运算符前后的数据，判断运算符表达的意义；
//4.错误输入：诸如1++的错误输入可以通过+字符前后数据ascii码取值判断；也可通过 数字数等于+-*/号数量+1判断；
//诸如（））错误可以通过）与（的数目是否对等判断。
//5.正确读取函数后，计算值。
//6.再利用牛顿迭代法对函数及其导数迭代操作。
