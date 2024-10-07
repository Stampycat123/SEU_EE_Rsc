#include <iostream>
#include <cstring>
#include <iomanip>
#include <algorithm>
using namespace std;

#define MAX_ERROR 0.0000001          // ǰ�����θ�˹ţ�ٵ���֮�����ֵ

// ����ʽ�����������֧��ͨ�����캯�����ó�ֵ��ͨ��GetRoot()�������
// ע�⣺F(), Diff() ��ʾ�������Լ�����
class FunctionResolver
{
private:
	double initValue;	//������ʼֵ
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
		// �������б�1������arr��arrSize�����������x����ֵ

		double sum = 0;
		double pi_ = 1;

		for (int i = 0; i < arrSize; ++i)
		{
			double coef = arr[i];
			// ����д����------------8��-------------------
			sum += coef * pow(x, i);
		}
		return sum;
	}

	virtual double Diff(const double x) const
	{
		// �������б�1������arr��arrSize�����������x���ĵ���
		// ����д����------------12��-------------------
		double sum = 0;
		double* arrDF = new double[arrSize];

		for (int i = 0; i < arrSize; ++i)
		{
			if (i == 0)
				arrDF[i] = 0;
			else
				arrDF[i] = arr[i] * i;
		}//�󵼺�ϵ��

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
		double xn_old;				//���б�Ҫ�������г�ʼ��

		// ��˹ţ�ٵ������ĵ������̴�����д ���������ε��� x
		// ��ֵС��MAX_ERROR(��0.0000001��ʱ�����˳�������
		// Ϊ��չʾ�������̣����ӡÿ�ε������ĸ�ֵ	
		// ����д����------------10��-------------------
		double f, f1;
		int i = 0;
		do
		{
			xn_old = xn;
			f = F(xn);
			f1 = Diff(xn);
			xn = xn_old - f / f1;

			i++;
			cout << "��" << i << "�ε�����x:\t" << setprecision(10) << xn << endl;
		} while (fabs(xn - xn_old) >= MAX_ERROR);

		return xn;
	}
};


int main()
{
	// ���4�� ������룬�� f(x) = 4 - x + 5 x**2 + x**3 ��-1������x��Ľ��� 
	cout << "Ϊ���ڹ۲죬�ѽ����������������Ϊ10" << endl;
	cout << "------------------------------------------------------" << endl;
	double cofs[4] = { 4, -1, 5, 1 };
	FunctionResolver fr(cofs, 4, -1);

	double root = fr.GetRoot();

	cout << "���̵Ľ�Ϊ��" << root << endl;
}


// �ش����⣨5�֣������Ҫ���һ��ͨ�÷����������
// �ʺϸ���ķ��̣������ο��ǣ����ñ�ѧ����ѧ��˵˵������롣

//��
//1.����cin.getline�����������룬���ַ�����ʽ����char*��������ĺ������޶�һ���ַ���ʹ�ã�
//2.����switch case������ascii����������ַ����б���������Ϊ��������������������¼������������±ꣻ
//3.ͨ���±����ĳ�����ǰ������ݣ��ж�������������壻
//4.�������룺����1++�Ĵ����������ͨ��+�ַ�ǰ������ascii��ȡֵ�жϣ�Ҳ��ͨ�� ����������+-*/������+1�жϣ�
//���磨�����������ͨ�����루����Ŀ�Ƿ�Ե��жϡ�
//5.��ȷ��ȡ�����󣬼���ֵ��
//6.������ţ�ٵ������Ժ������䵼������������
