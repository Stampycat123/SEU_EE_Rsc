#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	fstream in, out;
	in.open("scores.txt", ios::in);
	if (!in)
	{
		cout << "Can not open scores.txt!" << endl;
		exit(1);
	}
	out.open("result.txt", ios::out);
	if (!out)
	{
		cout << "Can not open result.txt!" << endl;
		exit(2);
	}
	int i = 0, a[1024];
	while (in >> a[i])i++;
	int total = i, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, max = 0, min = 0, sum = 0;
	for (i = 0; i < total; i++)
	{
		sum += a[i];
		if (max < a[i])max = a[i];
		if (min > a[i])min = a[i];
		if (a[i] < 60)a1++;
		else if (a[i] < 70)a2++;
		else if (a[i] < 80)a3++;
		else if (a[i] < 90)a4++;
		else a[5]++;
	}
	
	out << "��������" << total << '\n';
	out << "��߷֣�" << max << '\n';
	out << "��ͷ֣�" << min << '\n';
	out << "ƽ���֣�" << double(sum)/total << '\n\n';
	out << "90-100��" << a5 << "���ٷֱȣ�" << int(double(a5) / total) << "%" << '\n';
	out << " 80-89��" << a4 << "���ٷֱȣ�" << int(double(a4) / total) << "%" << '\n';
	out << " 70-79��" << a3 << "���ٷֱȣ�" << int(double(a3) / total) << "%" << '\n';
	out << " 60-69��" << a2 << "���ٷֱȣ�" << int(double(a2) / total) << "%" << '\n';
	out << "  0-59��" << a1 << "���ٷֱȣ�" << int(double(a1) / total) << "%" << '\n';
	out << endl;

	in.close();
	out.close();
	return 0;
}