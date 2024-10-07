#include<iostream>
#include<iomanip>
using namespace std;

class Student
{
	char Name[10], * Num;
	double Math, English, Physics, Cpp;
public:
	void setNameNo(char* name=NULL, char* no=NULL)
	{
		if (name)
			strcpy_s(Name, name);
		else
			strcpy_s(Name, "ERROR!");

		if (no)
		{
			Num = new char[strlen(no) + 1];
			strcpy_s(Num, strlen(no) + 1, no);
		}
		else
		{
			Num = new char[7];
			strcpy_s(Num, 7, "ERROR!");
		}

		cout << "学号、姓名已设置！" << endl;
	}

	void setScores(int m, int e, int p, int c)
	{
		Math = m;
		English = e;
		Physics = p;
		Cpp = c;

		cout << "成绩已导入！" << endl;
	}

	int total()
	{
		int sum;
		sum = Math + English + Physics + Cpp;
		return sum;
	}

	int average()
	{
		int ave;
		ave = total() / 4;
		return ave;
	}

	void outputInfo()
	{
		int sum, ave;
		sum = total();
		ave = average();
		
		cout << setw(8) << "姓名" << setw(10) << "学号" << setw(8) << "数学" << setw(8) << "英语" << setw(8) << "物理" << setw(8) << "C++" << setw(12) << "平均成绩" << endl;
		cout << setw(8) << Name << setw(10) << Num << setw(8) << Math << setw(8) << English << setw(8) << Physics << setw(8) << Cpp << setw(12) << ave << endl;
	}
};

int main()
{
	Student s1;
	char name[10], no[10];
	int m, e, p, c;

	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入学号：" << endl;
	cin >> no;
	s1.setNameNo(name, no);

	cout << "请分别输入数学、英语、物理、C++成绩：" << endl;
	cin >> m >> e >> p >> c;
	s1.setScores(m, e, p, c);

	s1.outputInfo();

	return 0;
}