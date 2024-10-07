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

		cout << "ѧ�š����������ã�" << endl;
	}

	void setScores(int m, int e, int p, int c)
	{
		Math = m;
		English = e;
		Physics = p;
		Cpp = c;

		cout << "�ɼ��ѵ��룡" << endl;
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
		
		cout << setw(8) << "����" << setw(10) << "ѧ��" << setw(8) << "��ѧ" << setw(8) << "Ӣ��" << setw(8) << "����" << setw(8) << "C++" << setw(12) << "ƽ���ɼ�" << endl;
		cout << setw(8) << Name << setw(10) << Num << setw(8) << Math << setw(8) << English << setw(8) << Physics << setw(8) << Cpp << setw(12) << ave << endl;
	}
};

int main()
{
	Student s1;
	char name[10], no[10];
	int m, e, p, c;

	cout << "������������" << endl;
	cin >> name;
	cout << "������ѧ�ţ�" << endl;
	cin >> no;
	s1.setNameNo(name, no);

	cout << "��ֱ�������ѧ��Ӣ�����C++�ɼ���" << endl;
	cin >> m >> e >> p >> c;
	s1.setScores(m, e, p, c);

	s1.outputInfo();

	return 0;
}