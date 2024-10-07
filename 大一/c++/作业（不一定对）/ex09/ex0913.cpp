#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct student
{
	char num[16], name[16];
	int age, score;
	student* next;
};

student* insert(student* head, student* p)
{
	student* p1, * p2 = NULL;//p2=pre

	if (!head)
	{
		head = p;
		p->next = NULL;
		return head;
	}

	p1 = head;
	while ((p->num) > (p1->num) && p1->next)
	{
		p2 = p1;
		p1 = p1->next;
	}
	
	if ((p->num) <= (p1->num))
	{
		p->next = p1;
		if (head == p1)
			head = p;
		else
			p2->next = p;
	}
	else
	{
		p1->next = p;
		p->next = NULL;
	}
	return head;
}

student* create()
{
	/*student* p = new student, * head = NULL;
	cout << "输入学号，以-1结束：" << endl;
	cin.getline(p->num, 16);
	while (!strcmp(p->num,"-1"))
	{
		strcpy_s(p->num, strlen(p->num)+1, p->num);
		if (!head)
			p->next = NULL;
		cout << "输入姓名、年龄、成绩：" << endl;
		cin >> p->name >> p->age >> p->score;
		head = insert(head, p);

		cout << "输入学号，以-1结束：" << endl;
		cin.getline(p->num, 16);
	}
	return head;*/
	student* head = NULL;

	while (1)
	{
		student* p = new student;
		cout << "输入学号，以-1结束：" << endl;
		cin >> p->num;

		if (!strcmp(p->num, "-1"))
		{
			delete p;
			break;
		}
		cout << "输入姓名、年龄、成绩：" << endl;
		cin >> p->name >> p->age >> p->score;
		p->next = NULL;
		head = insert(head, p);
	}
	return head;
}

void print(student* head)
{
	student* p = head;
	cout << setw(8) << "学号" << setw(8) << "姓名" << setw(8) << "年龄" << setw(8) << "成绩" << endl;
	while (p != NULL)
	{
		cout << setw(8) << p->num << setw(8) << p->name << setw(8) << p->age << setw(8) << p->score << endl;
		p = p->next;
	}
}

void delChain(student* head)
{
	student* p = head;
	while (head)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

int main()
{
	student* head;
	head = create();
	print(head);
	delChain(head);
	cout << "链表已释放！" << endl;
	return 0;
}