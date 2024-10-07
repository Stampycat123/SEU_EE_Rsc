#include<iostream>
#include<iomanip>
using namespace std;

class Node
{
	int data;
	Node* next;
public:
	friend class List;
	Node(int d):data(d),next(0)
	{
	}
};

class List
{
	Node* head;
public:
	List() :head(0)
	{
	}
	List(int d)
	{
		head = new Node(d);
	}
	void print()
	{
		Node* p = head;

		cout << "链表：";
		while (p)
		{
			cout << setw(8) << p->data;
			p = p->next;
		}
		cout << endl;
	}
	void append(int d = 0)
	{
		Node* p = head;
		while (p->next && p)
			p = p->next;
		if (p)
		{
			p->next = new Node(d);
		}
		else
		{
			head = new Node(d);
		}
	}
	~List()
	{
		while (head)
		{
			Node* p = head;
			head = head->next;
			delete p;
		}
		cout << "Dectructor Called!" << endl;
	}
};

int main()
{
	cout << "请输入首节点数据：" << endl;
	int d;
	cin >> d;
	List h1(d);
	h1.print();

	while (1)
	{
		cout << "请输入节点数据，输入-1结束：" << endl;
		cin >> d;
		if (d == -1)
			break;
		h1.append(d);
	}
	h1.print();

	return 0;
}
