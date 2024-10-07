#include<iostream>
#include<iomanip>
using namespace std;

class Student
{
	char Name[10], * Num;
	double Math, English, Physics, Cpp;
public:
	Student(char* Name = NULL, char* Num = NULL, int Math = 0, int English = 0, int Physics = 0, int Cpp = 0)
	{
		if (Name)
			strcpy_s(Student::Name, Name);
		else
			strcpy_s(Student::Name, "ERROR!");

		if (Num)
		{
			Student::Num = new char[strlen(Num) + 1];
			strcpy_s(Student::Num, strlen(Num) + 1, Num);
		}
		else
		{
			Student::Num = new char[7];
			strcpy_s(Student::Num, 7, "ERROR!");
		}

		Student::Math = Math;
		Student::English = English;
		Student::Physics = Physics;
		Student::Cpp = Cpp;
	}

	Student(Student&s)
	{
		Math = s.Math;
		English = s.English;
		Physics = s.Physics;
		Cpp = s.Cpp;
		if (s.Name)
			strcpy_s(Student::Name, s.Name);
		else
			strcpy_s(Student::Name, "ERROR!");
		if (s.Num)
		{
			Student::Num = new char[strlen(s.Num) + 1];
			strcpy_s(Student::Num, strlen(s.Num) + 1, s.Num);
		}
		else
		{
			Student::Num = new char[7];
			strcpy_s(Student::Num, 7, "ERROR!");
		}
	}

	~Student()
	{
		delete Num;
		cout << "Destructor Called!" << endl;
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
	char name[10], no[10];
	int m, e, p, c;

	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入学号：" << endl;
	cin >> no;
	cout << "请分别输入数学、英语、物理、C++成绩：" << endl;
	cin >> m >> e >> p >> c;

	Student s1(name, no, m, e, p, c);

	s1.outputInfo();

	return 0;
}