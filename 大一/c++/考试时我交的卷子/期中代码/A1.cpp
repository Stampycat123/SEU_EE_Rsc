#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;

//定义语言类型的枚举
//使用时可以直接使用 LanguageType::Chinese 代表汉语 等
//但是在打印输出，或赋值计算的过程中，LanguageType::Chinese 本质上就是整数 1
//LanguageType::English、LanguageType::Russian 等类似
enum LanguageType {
	Chinese = 1,
	English = 2,
	Russian = 3,
	Unknow = 0
};

//50分，5处填写程序，1处问答
class Book
{
private:
	char* title;            //书名
	char* author;           //作者
	LanguageType language;	//语言
	double price;           //单价

public:
	Book()
	{
		title = new char[100] {'\0'};
		author = new char [100] {'\0'};
		language = LanguageType::Chinese;
		price = 0;
	}

	Book(const char* newTitle, const char* newAuthor, LanguageType newLanguage, double newPrice)
		//四个参数分别代表书名、作者、语言、价格
	{
		//填写1，完成构造函数（10分）
		//注意对 title 和 author 进行必要的内存分配
		//这里需要将 newTitle 指针所指向的数组中的内容，全部拷贝到 title 指向的数组中
		//可以在循环中逐一拷贝，注意字符串以 '\0' 结尾，'\0' 之后的不需要拷贝
		//也可以调用 strcpy_s 函数完成此项功能
		//newAuthor => authoer 同样处理
		//另外还要完成 newLanguage => language，newPrice => price
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


	Book(const Book& bk)	 //复制构造函数
	{
		//填写2，完成复制构造函数（10分）
		//即要将 bk 中所有的成员复制到本对象中
		//注意对 title 和 author 进行必要的内存分配
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

	~Book()			        //析构函数
	{
		//填写3，完成析构函数（5分）
		//参照构造函数，完成必要的内存释放
		if (title)
			delete title;
		if (author)
			delete author;
	}


	void SetLanguage(LanguageType newLanguage)	 //修改语言
	{
		//填写4，完成语言修改（5分）
		language = newLanguage;

	}

	void Print(void)    //显示所有信息，语言应该输出对应字符串。
	{
		//填写5，完成数据输出（10分）
		//格式：
		//----------------------------------------
		// 书籍信息：
		//     书名：为什么是中国
		//     作者：金一南
		//     语言：中文（或者“英文”、“俄文”、“未知”）
		//     售价：58 元
		cout << "----------------------------------------" << endl << "书籍信息：" << endl;
		cout << "    " << "书名：" << title << endl;
		cout << "    " << "作者：" << author << endl;
		switch (language)
		{
		case Chinese:cout << "    " << "语言：" << "中文" << endl; break;
		case English:cout << "    " << "语言：" << "英文" << endl; break;
		case Russian:cout << "    " << "语言：" << "俄文" << endl; break;
		case Unknow:cout << "    " << "语言：" << "未知" << endl; break;
		default:break;
		}
		cout << "    " << "售价：" << price << " 元" << endl;
	}
};

int main()
{
	Book book1("为什么是中国", "金一南",  Chinese, 58.00);
	Book book2("边城",         "沈从文",  Chinese, 31.99);
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

//问答：在该类中，复制构造函数是否要显式的写出来？ 请总结一下，一般什么情况下必须要重载复制构造函数？
//10分，请在注解中直接作答
/*
需要。若不显式写出，系统自动生成的复制构造函数为：
title=newTitle;
author=newAuthor;
即地址值的赋值，为浅拷贝，内存将被释放两次。故需深拷贝，即重新分配内存并strcpy。
由上述可知，一般成员中含有char*类型时需重载。
*/







