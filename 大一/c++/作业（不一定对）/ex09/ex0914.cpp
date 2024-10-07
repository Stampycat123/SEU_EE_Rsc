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
		cout << "栈顶无元素！" << endl;
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
	cout << "输入整数据以入栈，输入-1停止：" << endl;
	cin >> d;
	while (d != -1)
	{
		head = push(head, d);
		cout << "输入整数据以入栈，输入-1停止：" << endl;
		cin >> d;
	}

	cout << "栈中元素：" << endl;
	display(head);

	d = getFirst(head);
	cout << "栈顶元素为：" << d << endl;
	head = pop(head, d);
	cout << "顶元素出栈后，栈中元素：" << endl;
	display(head);

	freeStack(head);
	/*cout << "撤销堆栈后，栈中元素：" << endl;
	display(head);*/
	cout << "链表已释放！" << endl;

	return 0;
}