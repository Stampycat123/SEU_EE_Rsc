#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

class Fraction
{
	//����������еĹ��졢��������������н���
	//��50�֣�
private:
	//����Ҫ�ĳ�Ա����
	int n;	//	�������
	int m;	//  �����ĸ

	//�绹Ҫ��Ҫ������Ա�����������в���



public:
	//����Ҫ�ĳ�Ա����
	void HuaJian()
	{
		int i;
		for (i = (m < n ? m : n); i >= 1; i--)
			if (m % i == 0 && n % i == 0)
				break;
		m /= i;
		n /= i;
	}
	//���������죬������ӣ���ĸ�� 1
	Fraction(int a             /* ������������д */)
	{
		//������������д
		n = a;
		m = 1;
	}

	//˫�������죬������ӡ���ĸ
	Fraction(int a,int b                                /* ������������д */)
	{
		//������������д
		m = b;
		n = a;
	}


	//AddWith
	void AddWith(Fraction item                       /* ���������в��� */)
	{
		//���������в���
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
	void MulWith(  Fraction &item                       /* ���������в��� */)
	{
		//���������в���
		m *= item.m;
		n *= item.n;


	}
	

	void Print() const
	{
		//���������в���
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
				cout << "�������� " << b << " / " << a << endl;
			else
				cout << "�������� " << b << endl;
		}
		else if (a < 0)
		{
			cout << "�������� " << (-1) * b << " / " << (-1) * a << endl;
		}

	}


	//�������Ҫ����������Ա�����������в���

};

//����һ��Fraction �����࣬��ɷ����ļ��㣬
//���е����ݶ������Է�������"a / b"����ʽ��������bΪ1����ֻ���a
//����ע�⣬ a/b ��Լ�ֺ�Ľ��

int main()
{
	//��� 1 + (1/2)*(1/2) + (1/3)*(1/3) + ... + (1/10)(1/10) �Ľ�� 
	//�Է�����ʽ���
	Fraction sum(0);			// sum = 0���� 0/1����������˵���������
	for (int i = 1; i <= 10; ++i)
	{
		Fraction item(1, i);	// ʵ�� item = 1/i
		item.MulWith(item);		// ʵ�� item = item * item
		sum.AddWith(item);		// ʵ�� sum += item
	}

	sum.Print();
}




