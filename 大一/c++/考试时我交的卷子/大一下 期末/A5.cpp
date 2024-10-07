#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;
#define KENNEL_MAX_SIZE 10
#define THRESHOLD_VALUE 11.5

class Filter
{
protected:
	string warningInfo;
	double kennel[KENNEL_MAX_SIZE];
	int kennelSize;

public:
	virtual int GetConvCore(double* kennel, int kenelMaxSize = KENNEL_MAX_SIZE) = 0;

	void Conv(double* x, int xSize)
	{
		// x: x 为待处理信号
		// xSize: 信号长度
		// 获得卷积核，放在成员 kennel 中
		// kennelSize 记录了卷积核 kennel 的有效长度
		kennelSize = this->GetConvCore(this->kennel, KENNEL_MAX_SIZE);

		//开始进行卷积
		for (int j = 0; j < xSize - kennelSize; ++j)
		{
			double sum = 0;
			// 实现 Sigma[0,kennelSize-1](kennel[i] * x[i + j]) ==> sum
			// 请填写代码------------10分-------------------
			for (int i = 0; i < kennelSize - 1; i++)
				sum += kennel[i] * x[i + j];



			// 对 sum 进行判别，如果 sum 超过阈值 THRESHOLD_VALUE 发出警报
			// 报警语句参考：cout << "在 " << j << " 位置，检测到 [" << warningInfo << "] 信号\n";
			// 请填写代码------------5分-------------------
			if(sum> THRESHOLD_VALUE)
				cout << "在 " << j << " 位置，检测到 [" << warningInfo << "] 信号\n";

		}
	}
};

class FilterA :public Filter
{
public:
	FilterA() { this->warningInfo = "上升沿"; }

	int GetConvCore(double* kennel, int kenelMaxSize = KENNEL_MAX_SIZE)
	{
		//参照赛题说明，设定卷积核为[-1, 0, 1]
		// 请填写代码------------5分-------------------
		double exactKen[3] = { -1,0,1 };
		int exactSize = 3;
		for (int i = 0; i < exactSize; i++)
			kennel[i] = exactKen[i];

		kenelMaxSize = exactSize;
		return kenelMaxSize;
	}
};

class FilterB :public Filter
{
public:
	FilterB() { this->warningInfo = "毛刺"; }

	int GetConvCore(double* kennel, int kenelMaxSize = KENNEL_MAX_SIZE)
	{
		//参照赛题说明，设定卷积核为[-1, 2, -1]
		// 请填写代码------------5分-------------------
		double exactKen[3] = { -1,2,-1 };
		int exactSize = 3;
		for (int i = 0; i < exactSize; i++)
			kennel[i] = exactKen[i];

		kenelMaxSize = exactSize;
		return kenelMaxSize;
	}
};

int main()
{
	double signal[] = { 1,1,12,14,12,10,6,20,7,5,3,2,1,1,10,14,13,12,12,12,9,7,17,1,1,1,0 };
	int signalSize = sizeof(signal) / sizeof(double);

	FilterA fa;
	fa.Conv(signal, signalSize);

	FilterB fb;
	fb.Conv(signal, signalSize);
	return 0;
}

//问：(5分）
// Filter如果要同时采用多个卷积核卷积并输出，从数据结构，到函数设置，你会采用怎样的策略？
//答：
//数据结构：double kennel[KENNEL_MAX_SIZE]设定为基类class Ken，Filter类中定义Ken数组，并新定义int n成员
//储存Ken数组的长度，实现多个卷积核的卷积操作。
//函数改变：将kennel形参改为指针类型，加上形参int n代表数组长度。
//函数体中增加外层循环，循环变量从0取到n-1，循环体中的kennel对应地改为Ken[k]，其中k为该外层新增的循环变量。
