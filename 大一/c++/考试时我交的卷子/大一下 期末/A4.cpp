#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

//存储集合的类
template<typename T>
class Collection
{
	T* data;			// 指向存储集合中数据的数组的指针
	int  capacity; 		// 集合的容量，即 data 指向的数组的长度
	int  count; 		// 集合中有效数据的个数（ 大于等于 0，且最大为 capacity）
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

private: //此对象禁止值拷贝
	Collection(const Collection& col) {}
	Collection<T>& operator =(const Collection<T>& col) {}

public:
	void Sort(bool desc = false)
	{
		// 完成Sort成员函数，对集合进行排序；
		// 参数desc为false时，从小到大排序，
		// 参数desc为true 时，从大到小排序，
		// 请填写代码------------15分-------------------
		int i, j;//循环变量

		if(desc)
		{
			for (i = 0; i < count - 1; i++)
				for (j = 0; j < count - 1 - i; j++)
					if (data[j] < data[j + 1])
					{
						T temp = data[j];
						data[j] = data[j + 1];
						data[j + 1] = temp;
					}//冒泡法排序
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

template<typename T> Collection<T>::Collection(int cap)	// 构造函数，初始化集合。
{
	if (cap <= 0) cap = 1;

	data = new T[cap];
	capacity = cap;
	count = 0;
}

template<typename T> Collection<T>::~Collection()		// 析构函数
{
	delete[] data;
}

//设置集合中的第 index 个数据
template<typename T>
void Collection<T>::SetValue(int index, const T& value) { data[index] = value; }

//要求：如果该元素已在集合，则不需要加入，不存在则加入，
//如果集合空间不够，自动扩容2倍，并输出“已扩容”的提示语句
template<typename T>
void Collection<T>::Add(const T& elem)
{
	int flag = 0; //标记elem是否存在集合中；
	for (int i = 0; i < count; i++)
	{
		if (data[i] == elem) {
			flag = 1; break;
		}
	}
	if (flag == 0)
	{
		if (count == capacity)//自动双倍扩容
		{
			capacity = 2 * capacity;
			T* newData = new T[capacity];
			for (int i = 0; i <= count - 1; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			cout << "已扩容" << endl;
		}
		data[count++] = elem;
	}
}

//删除集合中的第 index 个数字
template<typename T> void Collection<T>::RemoveAt(int index)
{
	if (index < 0)return;
	if (index >= count) return;

	for (int i = index + 1; i < count; ++i)
		data[i - 1] = data[i];

	count--;
}

//获得集合中第 index 个数据
template<typename T>
const T& Collection<T>::GetValue(int index) const { return data[index]; }

// 返回集合中有效数据的个数
template<typename T>
int Collection<T>::GetCount() const { return count; }

// 返回集合的容量
template<typename T>
int Collection<T>::GetCapacity() const { return capacity; }

// 打印集合
template<typename T>
void Collection<T>::Print(void) const
{
	for (int i = 0; i < count; i++)
	{
		cout << data[i] << "  ";
	}
	cout << endl;
}



class Fraction	//代表一个分数
{
	int num;	//分子
	int den;	//分母

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


	// 类Fraction表示一个分数，输出，但是没法参与Collection排序，
	// 请对Fraction进行适当改造，允许Fraction参与到Collection的排序中来，
	// 要求这种解决方案必须是符合工程规范的，能够适用于更广泛的场合，而非“临时性”的
	// 对Fraction进行适当改造
	// 请填写代码------------10分-------------------
	//最大公约数
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

	//最小公倍数
	int lcm(int a, int b)
	{
		return a / gcd(a, b) * b;
	}

	//分数化简函数
	void simplize()
	{
		if (num == 1 || num == 0 || den == 0)
			return;

		int res = gcd(num, den);
		num /= res;
		den /= res;
	}

	//化简后再计算，防止直接通分比较造成分子数据溢出
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



//问：(5分）
// 本题中线性表的设计存在哪些问题？能否进一步改进，如何改进？

//答：
//1.GetValue函数未判断是否溢出，可能会造成错误。
//改进：加上if(index > count) {cout << "数据溢出！"; return;}
//2.
