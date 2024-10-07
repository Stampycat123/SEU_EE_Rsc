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
		// x: x Ϊ�������ź�
		// xSize: �źų���
		// ��þ���ˣ����ڳ�Ա kennel ��
		// kennelSize ��¼�˾���� kennel ����Ч����
		kennelSize = this->GetConvCore(this->kennel, KENNEL_MAX_SIZE);

		//��ʼ���о��
		for (int j = 0; j < xSize - kennelSize; ++j)
		{
			double sum = 0;
			// ʵ�� Sigma[0,kennelSize-1](kennel[i] * x[i + j]) ==> sum
			// ����д����------------10��-------------------
			for (int i = 0; i < kennelSize - 1; i++)
				sum += kennel[i] * x[i + j];



			// �� sum �����б���� sum ������ֵ THRESHOLD_VALUE ��������
			// �������ο���cout << "�� " << j << " λ�ã���⵽ [" << warningInfo << "] �ź�\n";
			// ����д����------------5��-------------------
			if(sum> THRESHOLD_VALUE)
				cout << "�� " << j << " λ�ã���⵽ [" << warningInfo << "] �ź�\n";

		}
	}
};

class FilterA :public Filter
{
public:
	FilterA() { this->warningInfo = "������"; }

	int GetConvCore(double* kennel, int kenelMaxSize = KENNEL_MAX_SIZE)
	{
		//��������˵�����趨�����Ϊ[-1, 0, 1]
		// ����д����------------5��-------------------
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
	FilterB() { this->warningInfo = "ë��"; }

	int GetConvCore(double* kennel, int kenelMaxSize = KENNEL_MAX_SIZE)
	{
		//��������˵�����趨�����Ϊ[-1, 2, -1]
		// ����д����------------5��-------------------
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

//�ʣ�(5�֣�
// Filter���Ҫͬʱ���ö������˾��������������ݽṹ�����������ã������������Ĳ��ԣ�
//��
//���ݽṹ��double kennel[KENNEL_MAX_SIZE]�趨Ϊ����class Ken��Filter���ж���Ken���飬���¶���int n��Ա
//����Ken����ĳ��ȣ�ʵ�ֶ������˵ľ��������
//�����ı䣺��kennel�βθ�Ϊָ�����ͣ������β�int n�������鳤�ȡ�
//���������������ѭ����ѭ��������0ȡ��n-1��ѭ�����е�kennel��Ӧ�ظ�ΪKen[k]������kΪ�����������ѭ��������
