#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

//�洢���ϵ���
template<typename T>
class Collection
{
	T* data;			// ָ��洢���������ݵ������ָ��
	int  capacity; 		// ���ϵ��������� data ָ�������ĳ���
	int  count; 		// ��������Ч���ݵĸ����� ���ڵ��� 0�������Ϊ capacity��
public:
	Collection(int cap = 4);
	~Collection();
	void SetValue(int index, const T& value);
	void Add(const T& elem);
	void RemoveAt(int index);
	const T& GetValue(int index) const;
	int GetCount() const;
	int GetCapacity() const;
	void Print() const;

private: //�˶����ֵֹ����
	Collection(const Collection& col) {}
	Collection<T>& operator =(const Collection<T>& col) {}

public:
	void Sort(bool desc = false)
	{
		// ���Sort��Ա�������Լ��Ͻ�������
		// ����descΪfalseʱ����С��������
		// ����descΪtrue ʱ���Ӵ�С����
		// ����д����------------15��-------------------
		int i, j;//ѭ������

		if(desc)
		{
			for (i = 0; i < count - 1; i++)
				for (j = 0; j < count - 1 - i; j++)
					if (data[j] < data[j + 1])
					{
						T temp = data[j];
						data[j] = data[j + 1];
						data[j + 1] = temp;
					}//ð�ݷ�����
		}
		else
		{
			for (i = 0; i < count - 1; i++)
				for (j = 0; j < count - 1 - i; j++)
					if (data[j] > data[j + 1])
					{
						T temp = data[j];
						data[j] = data[j + 1];
						data[j + 1] = temp;
					}
		}
	}
};

template<typename T> Collection<T>::Collection(int cap)	// ���캯������ʼ�����ϡ�
{
	if (cap <= 0) cap = 1;

	data = new T[cap];
	capacity = cap;
	count = 0;
}

template<typename T> Collection<T>::~Collection()		// ��������
{
	delete[] data;
}

//���ü����еĵ� index ������
template<typename T>
void Collection<T>::SetValue(int index, const T& value) { data[index] = value; }

//Ҫ�������Ԫ�����ڼ��ϣ�����Ҫ���룬����������룬
//������Ͽռ䲻�����Զ�����2����������������ݡ�����ʾ���
template<typename T>
void Collection<T>::Add(const T& elem)
{
	int flag = 0; //���elem�Ƿ���ڼ����У�
	for (int i = 0; i < count; i++)
	{
		if (data[i] == elem) {
			flag = 1; break;
		}
	}
	if (flag == 0)
	{
		if (count == capacity)//�Զ�˫������
		{
			capacity = 2 * capacity;
			T* newData = new T[capacity];
			for (int i = 0; i <= count - 1; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			cout << "������" << endl;
		}
		data[count++] = elem;
	}
}

//ɾ�������еĵ� index ������
template<typename T> void Collection<T>::RemoveAt(int index)
{
	if (index < 0)return;
	if (index >= count) return;

	for (int i = index + 1; i < count; ++i)
		data[i - 1] = data[i];

	count--;
}

//��ü����е� index ������
template<typename T>
const T& Collection<T>::GetValue(int index) const { return data[index]; }

// ���ؼ�������Ч���ݵĸ���
template<typename T>
int Collection<T>::GetCount() const { return count; }

// ���ؼ��ϵ�����
template<typename T>
int Collection<T>::GetCapacity() const { return capacity; }

// ��ӡ����
template<typename T>
void Collection<T>::Print(void) const
{
	for (int i = 0; i < count; i++)
	{
		cout << data[i] << "  ";
	}
	cout << endl;
}



class Fraction	//����һ������
{
	int num;	//����
	int den;	//��ĸ

public:
	Fraction(int num = 0, int den = 1) :num(num), den(den) {}

	friend ostream& operator << (ostream& out, const Fraction& f)
	{
		if (f.den == 1)
			return out << f.num;
		else
			return out << f.num << "/" << f.den;
	}
	friend bool operator == (const Fraction& f1, const Fraction& f2)
	{
		return fabs(f1.num * 1.0 / f1.den - f2.num * 1.0 / f2.den) < 1E-10;
	}


	// ��Fraction��ʾһ�����������������û������Collection����
	// ���Fraction�����ʵ����죬����Fraction���뵽Collection������������
	// Ҫ�����ֽ�����������Ƿ��Ϲ��̹淶�ģ��ܹ������ڸ��㷺�ĳ��ϣ����ǡ���ʱ�ԡ���
	// ��Fraction�����ʵ�����
	// ����д����------------10��-------------------
	//���Լ��
	int gcd(int a, int b)
	{
		int res = a % b;
		while (res)
		{
			a = b;
			b = res;
			res = a % b;
		}
		return b;
	}

	//��С������
	int lcm(int a, int b)
	{
		return a / gcd(a, b) * b;
	}

	//����������
	void simplize()
	{
		if (num == 1 || num == 0 || den == 0)
			return;

		int res = gcd(num, den);
		num /= res;
		den /= res;
	}

	//������ټ��㣬��ֱֹ��ͨ�ֱȽ���ɷ����������
	friend bool operator > (Fraction& f1, Fraction& f2)
	{
		f1.simplize();
		f2.simplize();

		int newNum1, newNum2;
		newNum1 = f1.num * f2.den;
		newNum2 = f2.num * f1.den;

		return (newNum1 > newNum2);
	}

	friend bool operator < (Fraction& f1, Fraction& f2)
	{
		f1.simplize();
		f2.simplize();

		int newNum1, newNum2;
		newNum1 = f1.num * f2.den;
		newNum2 = f2.num * f1.den;

		return (newNum1 < newNum2);
	}


};

int  main()
{
	Collection<Fraction> fc;
	fc.Add(Fraction(1, 2));
	fc.Add(Fraction(3, 2));
	fc.Add(Fraction(1, 6));
	fc.Add(Fraction(7, 9));
	fc.Add(Fraction(2, 3));
	fc.Add(Fraction(5, 6));
	fc.Sort(true);

	fc.Print();

	return 0;
}



//�ʣ�(5�֣�
// ���������Ա����ƴ�����Щ���⣿�ܷ��һ���Ľ�����θĽ���

//��
//1.GetValue����δ�ж��Ƿ���������ܻ���ɴ���
//�Ľ�������if(index > count) {cout << "���������"; return;}
//2.
