#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
#define PI 3.1415926535897

//�洢���ϵ���
class Collection
{
	int* data;			// ָ��洢���������ݵ������ָ��
	int  capacity; 		// ���ϵ��������� data ָ�������ĳ���
	int  count; 		// ��������Ч���ݵĸ����� ���ڵ��� 0�������Ϊ capacity��
public:
	Collection(int capacity = 100)	// ���캯������ʼ�����ϡ����� capacity ָ���˼����ڴ�����Ĵ�С��Ĭ�� 100
	{
		//��д1�� ��ɹ��캯����5�֣�
		// ��
		// �� data �ڴ�����룬
		// �Լ��� this->capacity��this->count �ĳ�ʼ��
		// ����һ��ʼ�����ǿյģ�this->count һ��ʼӦΪ 0
		this->capacity = capacity;
		this->count = 0;
		data = new int[capacity];

	}

	~Collection()		// ��������
	{
		delete[] data;
	}

	void SetCapacity(int newCapacity)//  �������볤��ΪnewCapacity�Ķ�̬�ռ�
	{
		//��д2������������ʱ�����ô˺������¶���������10�֣�
		//��ҪҪ��ԭ���� data ɾ����������ԭ��������
		if (capacity < newCapacity)
		{
			capacity = newCapacity;
			int* newPtr;
			newPtr = new int[newCapacity];
			for (int i = 0; i < count; i++)
				newPtr[i] = data[i];
			delete data;
			data = newPtr;
		}
		
	}

	void Print(void) const
	{
		for (int i = 0; i < count; i++)
			cout << data[i] << "  ";
		cout << endl;
	}

	//���ü����еĵ� index ������
	void SetValue(int index, int value) { data[index] = value; }

	//�򼯺������һ������
	void Add(int value)
	{
		if (count < capacity)
			data[count++] = value;
	}

	//ɾ�������еĵ� index ������
	void RemoveAt(int index)
	{
		if (index < 0)return;
		if (index >= count) return;

		for (int i = index + 1; i < count; ++i)
			data[i - 1] = data[i];

		count--;
	}

	//��ü����е� index ������
	int GetValue(int index) const { return data[index]; }

	// ���ؼ�������Ч���ݵĸ���
	int GetCount() const { return count; }

	// ���ؼ��ϵ�����
	int GetCapacity() const { return capacity; }

	friend void Union(Collection& a, const Collection& b); //  ���������ϣ����� a ��
	friend void Intersect(Collection& a, const Collection& b); //  ���������ϣ����� a ��

};

void Union(Collection& a, const Collection& b) //  ���������ϣ����� a ��
{
	//��д3��a��b �ϲ��� a ��15 �֣�
	//ע�⣺
	// 1. ע���� a ��������������Ҫ����
	// 2. �����ظ�������

	bool equal = 0;
	int count = a.count;
	for (int i = 0; i < b.count; i++)
	{
		if (count == a.capacity-1)
			a.SetCapacity(a.capacity + 10);
		for (int j = 0; j < a.count; j++)
			if (a.data[j] == b.data[i])
				equal = 1;
		if (!equal)
		{
			a.data[count] = b.data[i];
			count++;
		}
		equal = 0;
	}
	a.count = count;
}

void Intersect(Collection& a, const Collection& b) //  ���������ϣ����� a ��
{
	//��д4��a��b �ཻ�� a ��10 �֣�
	bool equal = 0;
	int temp[100] = { 0 }, k = 0;
	for (int i = 0; i < a.count; i++)
	{
		for (int j = 0; j < b.count; j++)
			if (a.data[i] == b.data[j])
				equal = 1;
		
		if (equal)
			temp[k++] = a.data[i];
	}
	delete a.data;
	a.data = new int[a.capacity];
	a.count = k;
	for (int i = 0; i < a.count; i++)
		a.data[i] = temp[i];
	
}

int  main()
{
	//TEST A:
	{
		Collection a(5);		//����Ϊ 5
		Collection b(5);		//����Ϊ 5
		a.Add(5); a.Add(7); a.Add(3); a.Add(1);
		b.Add(2); b.Add(1); b.Add(3); b.Add(9);

		Union(a, b);

		cout << "�ϲ���� a��";
		a.Print();
	}

	//TEST B:
	{
		Collection a(5);		//����Ϊ 5
		Collection b(5);		//����Ϊ 5
		a.Add(5); a.Add(7); a.Add(3); a.Add(1);
		b.Add(2); b.Add(1); b.Add(3); b.Add(9);

		Intersect(a, b);

		cout << "�ཻ��� a��";
		a.Print();
	}

	return 0;
}



//�ʣ�(10�֣���
// friend void Union(Collection& A, const Collection& b); 
// �����е�һ������Ϊʲô�����ô��ݣ����Ըĳ�ֵ������Ϊʲô��
//���ܣ���Ϊ�˴��Ƕ�a��data���в��������ô��ݿ���ֱ�Ӷ�a��data��Ա���в�����������Ϊ���ã�����ʵ�ζ��β�a�ĳ�ʼ������һ����ʱ�����ں�������ʱ����������˲��ܸĳ�ֵ���ݡ�



