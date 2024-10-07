#include<iostream>
using namespace std;

class PolyLine;

//��Point�Ķ��� 
class Point
{
	double x, y;
public:
	//ȱʡ���캯��
	Point(double px = 0, double py = 0) :
		x(px), y(py)
	{
	}

	//����������ȫ������  
	friend ostream& operator<<(ostream& out, const Point& p);
	friend class PolyLine;
};

//����������ȫ������  
ostream& operator<<(ostream& out, const Point& p)
{
	//����д����------------6��-------------------
	out << "(" << p.x << " , " << p.y << ")";
	return out;
}

//��PolyLine�Ķ��� 
class PolyLine
{
	Point* pLine;
	int size;
public:
	//���캯������̬����ռ� 
	PolyLine(double* xArr, double* yArr, int size)
	{
		this->size = size;
		pLine = new Point[size];

		for (int i = 0; i < size; i++)
		{
			pLine[i].x = xArr[i];
			pLine[i].y = yArr[i];
		}
	}


	//����p��ӵ������С�ע�⣬���ڿռ䲻������Ҫ���·���ռ䣨3�֣���
	//������¾�����֮��Ŀ�����3�֣����ټ��������ݣ�3�֣���
	//ͬʱ���÷����ڴ�й©��3�֣�
	PolyLine& operator+=(const Point& p)
	{
		//����д����------------12��------------------
		int newSize = size + 1, i;
		Point* newPLine = new Point[newSize];
		

		for (i = 0; i < size; i++)
		{
			newPLine[i].x = pLine[i].x;
			newPLine[i].y = pLine[i].y;
		}
		newPLine[i].x = p.x;
		newPLine[i].y = p.y;

		delete pLine;
		size = newSize;
		pLine = newPLine;
		return *this;
	}

	// ��ȡ�����ϵ�i���������  
	Point operator[](int i) const
	{
		//����д����------------4��-------------------
		if (i >= size)
		{
			cout << "�±�Խ�磡" << endl;
			return NULL;
		}
		return pLine[i];

	}

	//�����������ͷŶ�̬����ռ�
	~PolyLine()
	{
		delete[] pLine;
	}

	int getSize()const
	{
		return size;
	}
	int getSize()
	{
		return size;
	}

};

//�����������غ�����������������е������             
ostream& operator<<(ostream& out, const PolyLine& pl)
{
	//����д����------------6��-------------------
	//����û�� friend �����������������
	//ע�⣺���б�Ҫ�����Զ�PolyLine������ʵ����죬�����ÿ����Ա���������Ԫ
	int i;
	for (i = 0; i < pl.getSize(); i++)
	{
		out << pl[i] << '\t';
		if ((i + 1) % 5 == 0)
			out << endl;//�������㻻��
	}
	return out;
}


int main()
{
	double xArr[] = { 0,   7.7,  32.6, 12.4,  20.1,     0 };  //�������ж�Ӧ���x����
	double yArr[] = { 0, -23.7, -23.7, 38.4, -62.1, -47.4 };  //�������ж�Ӧ���y����

	PolyLine poly(xArr, yArr, 6);
	cout << "���ݵ㣺\n" << poly << endl << endl;

	poly += poly[0];    //�����ߵĵ�0��������ֵ��ӵ��������
	cout << "������ݵ��\n" << poly << endl;
	return 0;
}

//��ע���лش����⣺��7�֣�
// ������Ŀ�е�һ���˻��Ի��Ի���˵һ˵����ʵ��PolyLine��ġ�<<������Ԫ����ʱ���Ĺ�����
// ��PolyLine����Point��ʵ�����ǡ����ʶ����Ա�ĳ�Ա�������⡣�ڲ�ͨ����Ԫʵ�֡�<<������ʱ�����ڷ���Ȩ�޵����⣬�޷�ֱ�Ӷ�Point��PolyLine���е�˽���������ͽ��з��ʣ������Ҫ���нӿں�����
// ������getSize�����Ի�ȡ��ǰ����ĳ��ȣ��Ե�ķ�������������ġ�[]�����ء�
// �������ء�<<�����β���const���ͣ����getSize��Ҫ����Ϊ����Ա�����Է��ʡ�
// 
// 
// �ͶԻ��е�������ƥ��������Ӧ������ͨ�÷���������Ϊ������ͨ������ʱ������
// ƥ�䡣����Ԫ�ǳ�Ա�������к������أ���˽�����ݳ�Ա���з��ʣ�ʵ���Ͻ�����ǽӿ����⣬��������Ľ����ͨ����Ա�����ӿ�ʵ�ֵġ�
//��˷���������