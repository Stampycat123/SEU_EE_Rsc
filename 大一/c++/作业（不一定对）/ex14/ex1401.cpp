#include<iostream>
using namespace std;

class Student
{
	char name[64], num[64];
	int c, mat, phy;
public:
	Student(char* na = NULL, char* nu = NULL, int cc = 0, int m = 0, int p = 0)
	{
		strcpy_s(name, na);
		strcpy_s(num, nu);
		c = cc;
		mat = m;
		phy = p;
	}

	operator char* ()
	{
		return name;
	}

	operator int()
	{
		return c + mat + phy;
	}

	friend istream& operator>>(istream& in, Student& stu); 
	friend ostream& operator<<(ostream& out, Student& stu);
};

istream& operator>>(istream& in, Student& stu)
{
	in >> stu.name;
	in >> stu.num;
	in >> stu.c >> stu.mat >> stu.phy;
	return in;
}

ostream& operator<<(ostream& out, Student& stu)
{
	int i = 0, j = 0;
	while (stu.name[i] != '\0')
		out << stu.name[i++];
	out << '\t';
	while (stu.num[j] != '\0')
		out << stu.num[j++];
	out << '\t';
	out << stu.c<<'\t';
	out << stu.mat<<'\t';
	out << stu.phy<<'\n';
	return out;
}

int main()
{
	Student stud;
	char* p;
	int total;
	cin >> stud;
	cout << stud;
	p = stud;
	total = stud;

	cout << p << endl;
	cout << "×Ü³É¼¨£º" << total << endl;

	return 0;
}