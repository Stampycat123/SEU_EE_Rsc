#include <iostream>
#include <iomanip>
using namespace std;

struct node
{
	int data;
	struct node* next;
};

node* push(node* head, int d)
{
	node* p = new node;
	p->data = d;
	p->next = head;
	return p;
}

node* pop(node* head, int& d)
{
	node* p = head;
	if (p != NULL)
	{
		d = head->data;
		head = head->next;
		delete p;
	}
	else
		cout << "ջ����Ԫ�أ�" << endl;
	return head;
}

int getFirst(node* head)
{
	if (head != NULL)
		return head->data;
	return NULL;
}

void display(node* head)
{
	node* p;

	p = head;
	if (p != NULL)
	{
		while (p)
		{
			cout << p->data << endl;
			p = p->next;
		}
	}
	else
		cout << "NULL" << endl;
	cout << endl;
}

void freeStack(node* head)
{
	node* p = head;
	while (head)
	{
		p = head;
		head = head->next;
		delete p;
	}
	cout << endl;
}

int main()
{
	int d;
	node* head = NULL;
	cout << "��������������ջ������-1ֹͣ��" << endl;
	cin >> d;
	while (d != -1)
	{
		head = push(head, d);
		cout << "��������������ջ������-1ֹͣ��" << endl;
		cin >> d;
	}

	cout << "ջ��Ԫ�أ�" << endl;
	display(head);

	d = getFirst(head);
	cout << "ջ��Ԫ��Ϊ��" << d << endl;
	head = pop(head, d);
	cout << "��Ԫ�س�ջ��ջ��Ԫ�أ�" << endl;
	display(head);

	freeStack(head);
	/*cout << "������ջ��ջ��Ԫ�أ�" << endl;
	display(head);*/
	cout << "�������ͷţ�" << endl;

	return 0;
}