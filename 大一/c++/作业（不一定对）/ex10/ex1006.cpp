#include<iostream>
using namespace std;
class ListClass
{
	char* ListPtr;
	int nLen;
	int nElem;
public:
	ListClass(int n = 10)
	{
		nElem = 0;
		nLen = n;
		if (n)
			ListPtr = new char[n];
		else
			ListPtr = 0;
	}
	~ListClass(void)
	{
		delete[nLen]ListPtr;
	}
	char Elem(char);
	char& Elem(unsigned n)
	{
		return ListPtr[n];
	}
	int Elem(void)
	{
		return nElem;
	}
	int Len(void)
	{
		return nLen;
	}
	char GetElem(int i)
	{
		if ((i >= 0) && i < nElem)
			return ListPtr[i];
		else
		{
			cout << "�±�Խ��" << endl;
			return (-1);
		}
	}
	void Print(void);
};

char ListClass::Elem(char elem)
{
	if (nElem == nLen)
	{
		char* newptr;
		newptr = new char[nLen + 10];
		strcpy_s(newptr, nElem, ListPtr);
		delete[nLen]ListPtr;
		nLen += 10;
		ListPtr = newptr;
	}
	ListPtr[nElem++] = elem;
	return nElem;
}

void ListClass::Print(void)
{
	cout << ListPtr;
	cout << endl;
}

int main(void)
{
	ListClass list(6);
	for (int i = 0; i < 5; i++)
		list.Elem(char(i));
	cout << "���Ա�ĳ���Ϊ��" << list.Len() << endl;
	cout << "���Ա��Ԫ�ظ���Ϊ��";
	cout << list.Elem() << endl;
	cout << "���Ա��Ԫ��Ϊ��";
	list.Print();
	list.Elem(3u) = 100;
	cout << "���Ա��±�Ϊ3��Ԫ�ص�ֵΪ��";
	cout << list.Elem(3u) << endl;
	list.Elem(char(20));
	list.Elem(char(200));
	cout<<"�������Ա�ĳ���Ϊ��" << list.Len() << endl;
	cout << "�������Ա��Ԫ�ظ���Ϊ��";
	cout << list.Elem() << endl;
	cout << "���Ա��Ԫ��Ϊ��";
	list.Print();
	cout << "���Ա�����һ��Ԫ��Ϊ��";
	cout << list.GetElem(list.Elem() - 1) << endl;
	return 0;
}