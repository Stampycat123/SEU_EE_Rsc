#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

//�����������͵�ö��
//ʹ��ʱ����ֱ��ʹ�� LanguageType::Chinese ������ ��
//�����ڴ�ӡ�������ֵ����Ĺ����У�LanguageType::Chinese �����Ͼ������� 1
//LanguageType::English��LanguageType::Russian ������
enum LanguageType {
	Chinese = 1,
	English = 2,
	Russian = 3,
	Unknow = 0
};

//50�֣�5����д����1���ʴ�
class Book
{
private:
	char* title;            //����
	char* author;           //����
	LanguageType language;	//����
	double price;           //����

public:
	Book()
	{
		title = new char[100] {'\0'};
		author = new char [100] {'\0'};
		language = LanguageType::Chinese;
		price = 0;
	}

	Book(const char* newTitle, const char* newAuthor, LanguageType newLanguage, double newPrice)
		//�ĸ������ֱ�������������ߡ����ԡ��۸�
	{
		//��д1����ɹ��캯����10�֣�
		//ע��� title �� author ���б�Ҫ���ڴ����
		//������Ҫ�� newTitle ָ����ָ��������е����ݣ�ȫ�������� title ָ���������
		//������ѭ������һ������ע���ַ����� '\0' ��β��'\0' ֮��Ĳ���Ҫ����
		//Ҳ���Ե��� strcpy_s ������ɴ����
		//newAuthor => authoer ͬ������
		//���⻹Ҫ��� newLanguage => language��newPrice => price
		language = newLanguage;
		price = newPrice;
		if (newTitle)
		{
			title = new char[strlen(newTitle) + 1];
			strcpy_s(title, strlen(newTitle) + 1, newTitle);
		}
		else
			title = NULL;
		if (newAuthor)
		{
			author = new char[strlen(newAuthor) + 1];
			strcpy_s(author, strlen(newAuthor) + 1, newAuthor);
		}
		else
			author = NULL;
	
	}


	Book(const Book& bk)	 //���ƹ��캯��
	{
		//��д2����ɸ��ƹ��캯����10�֣�
		//��Ҫ�� bk �����еĳ�Ա���Ƶ���������
		//ע��� title �� author ���б�Ҫ���ڴ����
		language = bk.language;
		price = bk.price;
		if (title)
			delete title;
		if (author)
			delete author;
		if (bk.title)
		{
			title = new char[strlen(bk.title) + 1];
			strcpy_s(title, strlen(bk.title) + 1, bk.title);
		}
		else
			title = NULL;
		if (bk.author)
		{
			author = new char[strlen(bk.author) + 1];
			strcpy_s(author, strlen(bk.author) + 1, bk.author);
		}
		else
			author = NULL;
	
	}

	~Book()			        //��������
	{
		//��д3���������������5�֣�
		//���չ��캯������ɱ�Ҫ���ڴ��ͷ�
		if (title)
			delete title;
		if (author)
			delete author;
	}


	void SetLanguage(LanguageType newLanguage)	 //�޸�����
	{
		//��д4����������޸ģ�5�֣�
		language = newLanguage;

	}

	void Print(void)    //��ʾ������Ϣ������Ӧ�������Ӧ�ַ�����
	{
		//��д5��������������10�֣�
		//��ʽ��
		//----------------------------------------
		// �鼮��Ϣ��
		//     ������Ϊʲô���й�
		//     ���ߣ���һ��
		//     ���ԣ����ģ����ߡ�Ӣ�ġ��������ġ�����δ֪����
		//     �ۼۣ�58 Ԫ
		cout << "----------------------------------------" << endl << "�鼮��Ϣ��" << endl;
		cout << "    " << "������" << title << endl;
		cout << "    " << "���ߣ�" << author << endl;
		switch (language)
		{
		case Chinese:cout << "    " << "���ԣ�" << "����" << endl; break;
		case English:cout << "    " << "���ԣ�" << "Ӣ��" << endl; break;
		case Russian:cout << "    " << "���ԣ�" << "����" << endl; break;
		case Unknow:cout << "    " << "���ԣ�" << "δ֪" << endl; break;
		default:break;
		}
		cout << "    " << "�ۼۣ�" << price << " Ԫ" << endl;
	}
};

int main()
{
	Book book1("Ϊʲô���й�", "��һ��",  Chinese, 58.00);
	Book book2("�߳�",         "�����",  Chinese, 31.99);
	Book book3("Sun and Moon", "Johnson", English, 25.40);
	Book book4 = book2;

	book1.Print();
	book2.Print();
	book3.Print();
	book4.Print();

	book3.SetLanguage(LanguageType::Russian);

	book3.Print();

	return 0;
}

//�ʴ��ڸ����У����ƹ��캯���Ƿ�Ҫ��ʽ��д������ ���ܽ�һ�£�һ��ʲô����±���Ҫ���ظ��ƹ��캯����
//10�֣�����ע����ֱ������
/*
��Ҫ��������ʽд����ϵͳ�Զ����ɵĸ��ƹ��캯��Ϊ��
title=newTitle;
author=newAuthor;
����ֵַ�ĸ�ֵ��Ϊǳ�������ڴ潫���ͷ����Ρ���������������·����ڴ沢strcpy��
��������֪��һ���Ա�к���char*����ʱ�����ء�
*/







