#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#include<iomanip>
using namespace std;
#define LEN sizeof(Timetable)

typedef struct
{
	char no[16];//Ϊʲô�̲���char���ͣ�
	int hour;
	int minute;
	char Starting_station[16];
	char Last_station[16];
	float time;
	int fare;
	int max_number;
	int sold_number;
}Timetable;
char busFile[] = "bus.txt";


//-------------------------------------------------------����������-----------------------------------------------------
//�����˵�����
	void AdminMode(Timetable * timetables, char* filename);
	void PassagerMode(Timetable * timetables, char* filename);
	int MainWindowSelect();
	int AdminWindowSelect();
	int PassagerWindowSelect();
	//�˵����ܴ�����
	void Signin();
	int ReadFromFile(Timetable * timetables, int n, char* filename);
	int AddBus(Timetable * timetables, int n);
	int WritetoFile(Timetable * timetables, int n, char* filename);
	void ShowBusInfo(Timetable * timetables, int n, int idx);
	void ShowTimetable(Timetable * timetables, int n);
	void Query(Timetable * timetables, int n); int find(Timetable * timetables, int n, char* no);
	int find(Timetable * timetables, int n, char* Last_station, int* b);
	int DelBus(Timetable * timetables, int n);
	void GenerateLogFileName(char* LogFileName);
	int InitializationPassagerMode(Timetable * timetables, char* LogFileName, char* filename);
	void TicketOrder(Timetable * timetables, int n);
	void TicketDelete(Timetable * timetables, int n);
	int StopSevice(Timetable * timetables, int n, char* no);
	void SortbyTime(Timetable * timetables, int n);
	int Quit();
	void OutPutBusList();


//-------------------------------------------------��������------------------------------------------------------
int main()
{
	int UserChoice;
	Timetable timetables[100];
	while (1)
	{
		switch (UserChoice = MainWindowSelect())
		{
		case 1:AdminMode(timetables, busFile); break;
		case 2:PassagerMode(timetables, busFile); break;
		case 3:if (Quit() != 1)continue;
		}
		if (UserChoice == 3)break;
	}
	return 0;
}


//------------------------------------------------�˵�������--------------------------------------------------
void AdminMode(Timetable* timetables, char* filename)
{
	Signin();
	int n = ReadFromFile(timetables, 0, busFile);
	while (1)
	{
		system("cls");

		int AdminChoice = AdminWindowSelect();
		switch (AdminChoice)
		{
		case 1:n = AddBus(timetables, n); WritetoFile(timetables, n, filename);
			system("pause"); break;
		case 2:ShowTimetable(timetables, n); system("pause"); break;
		case 3:Query(timetables, n); system("pause"); break;
		case 4:n = DelBus(timetables, n); system("pause");
			WritetoFile(timetables, n, filename); break;
		case 5:WritetoFile(timetables, n, filename);
			return;
		}
	}
}


void PassagerMode(Timetable* timetables, char* filename)
{
	char LogFileName[200];
	GenerateLogFileName(LogFileName);
	int n = InitializationPassagerMode(timetables, LogFileName, filename);
	int PassagerChoice;
	while (1)
	{
		system("cls");

		switch (PassagerChoice = PassagerWindowSelect())
		{
		case 1:Query(timetables, n); system("pause"); break;
		case 2:TicketOrder(timetables, n); WritetoFile(timetables, n, LogFileName);
			system("pause"); break;
		case 3:TicketDelete(timetables, n); WritetoFile(timetables, n, LogFileName);
			system("pause"); break;
		case 4: WritetoFile(timetables, n, LogFileName);
			return;
		}
	}
}


int MainWindowSelect()
{
	const char* m[4] = { "1.����Ա��¼",
		"2.��ͨ�˿͵�¼",
		"3.�˳�" };
	int i, choice;
	do {
		system("cls");
		for (i = 0; m[i]; i++)
			cout << m[i] << endl;
		cout << "������ѡ��";
		cin >> choice;//�˴����������aʱ������
	} while (choice < 1 || choice>3);
	return(choice);
}


int AdminWindowSelect()
{
	const char* am[6] = { "1.���ӳ�����Ϣ","2.�鿴���г�����Ϣ","3.������Ϣ��ѯ","4.ע������","5.�˳�"};
	int choice;
	do {
		system("cls");
		for (int i = 0; am[i]; i++)
			cout << am[i] << endl;
		cout << "������ѡ��";
		cin >> choice;
	} while (choice < 1 || choice>5);
	return(choice);
}


int PassagerWindowSelect()
{
	const char* pm[5] = { "1.������Ϣ��ѯ","2.����Ʊ","3.��Ʊ","4.�˳�" };
	int choice;
	do {
		system("cls");
		for (int i = 0; i < 4; i++)
			cout << pm[i] << endl;
		cout << "������ѡ��";
		cin >> choice;
	} while (choice < 1 || choice>4);
	return(choice);
}


//1
//?����д
//void Signin()
//{
//	int i, j;
//	char name[16] = { '\0' };
//loop:	char password[32] = { '\0' };
//	cout << "�������û�����";
//	cin >> name;
//	cin.ignore();//�����뻻�з�
//	if (!strcmp(name ,"admin"))
//	{
//		cout << "\n���������룺";
//		system("cls");
//
//		i = 0;
//		cout << "�������û�����";
//		cout << name << endl;
//		cout << "\n���������룺";
//		for (j = 0; j < i; j++)
//			cout << "*";
//		password[i] = _getch();
//		if (password[i] == '\b')
//		{
//			password[i] = '\0';
//			i--;
//
//			if (i != -1)
//				i--;
//		}
//		system("cls");
//		i++;
//
//		if (!strcmp(password,"123") && !strcmp(name,"admin"))
//		{
//			system("cls");
//			cout << "��¼�ɹ������ڽ������Ա����" << endl;
//		}
//		else
//		{
//			cout << "������û�������������" << endl;
//			goto loop;
//		}
//	}
//	else
//	{
//		cout << "�û������ڣ�" << endl;
//		goto loop;
//	}
//}


//------------------------------------------------------���ܺ�����------------------------------------------------
//1
void Signin()
{
	int i;//����ѭ�����������������
	int j = 0;
	char account[32];


	while (1)
	{
		char password[64] = { '\0' };//����

		cout << "��ӭʹ������վ��Ʊ����ϵͳ\n\n";
		cout << "�˺ţ�";
		cin >> account;//�˺�
		cin.ignore();//����ȡ���з�
		cout << "\n���룺";
		system("cls");

		//�������루�ظ���������
		i = 0;
		while (1)
		{
			cout << "��ӭʹ������վ��Ʊ����ϵͳ\n\n";
			cout << "�˺ţ�";
			cout << account << endl;
			cout << endl;
			cout << "���룺";

			for (j = 0; j < i; j++)
				cout << "*";

			password[i] = _getch();

			if (password[i] == '\r')
				break;

			//����backspaceɾ��*��
			if (password[i] == '\b')
			{
				password[i] = '\0';
				i--;

				//δ����״̬�£�����0�������ַ�ʱ����backspace�������
				if (i == -1)
					i++;
			}
			else
				i++;
			system("cls");

			if (i > 20)
				break;
		}

		if (!strcmp(account, "admin") && !strcmp(password, "123\r"))
		{
			system("cls");
			return;
		}

		cout << "\n\n\n";
		cout << "������˺Ż���������\n";

		system("pause");
		system("cls");
	}
}


//2
int ReadFromFile(Timetable* timetables, int n, char* filename)
{
	fstream file;
	file.open(filename, ios::in);
	//�Ҳ����ļ�ʱ��
	if (file.fail())
	{
		cout << "�ļ������ڣ�\n\n";
		exit(1);
	}
	//�ҵ��ļ���
	while (!file.eof())
	{
		//----------------------------------------------------����ѭ�����˴���ʼ���󣬵���֪Ϊ��
		//---------------------------------------------------�����Ѹ���
		file >> timetables[n].no;
		//��ֹ��һ���ǿյı���ȡ��ȥ��
		if (file.eof())
		{
			file.close();
			break;
		}
		file >> timetables[n].hour;
		file >> timetables[n].minute;
		file >> timetables[n].Starting_station;
		file >> timetables[n].Last_station;
		file >> timetables[n].time;
		file >> timetables[n].fare;
		file >> timetables[n].max_number;
		file >> timetables[n].sold_number;
		n++;
	}
	file.close();
	return n;
}


//3
int AddBus(Timetable* timetables, int n)
{
	int i, state;//state�жϳ����Ƿ��Ѵ��ڣ�״̬0����δ�����ظ�

	while(1)
	{
		state = 0;
		cout << "\n\n�����복�κ�:";
		cin >> timetables[n].no;
		cout << endl;
		//Ѱ���ظ�����
		for (i = 0; i < n; i++)
			if (!strcmp(timetables[i].no, timetables[n].no))
				state = 1;

		if (!state)
			break;
		else
			cout << "�Ѵ�����ͬ����";
	}

	cout << "���������ʱ�䣨Сʱ����";
	cin >> timetables[n].hour;
	cout << endl;
	cout << "���������ʱ�䣨���ӣ���";
	cin >> timetables[n].minute;
	cout << endl;
	cout << "��������ʼվ��";
	cin >> timetables[n].Starting_station;
	cout << endl;
	cout << "�������յ�վ��";
	cin >> timetables[n].Last_station;
	cout << endl;
	cout << "����������г�ʱ�䣺";
	cin >> timetables[n].time;
	cout << endl;
	cout << "������Ʊ�ۣ�";//Ϊ������û��Ҫ������Ʊ�ۣ�
	cin >> timetables[n].fare;
	cout << endl;
	cout << "�������ؿ�����";
	cin >> timetables[n].max_number;
	timetables[n].sold_number = 0;//����Ʊ��Ϊ0
	n++;

	return n;
}


//4
int WritetoFile(Timetable* timetables, int n, char* filename)
{
	if (n == 0)
		return 0;//���ж��Ƿ���Ҫд��
	fstream file;//�ļ�
	SortbyTime(timetables, n);//����

	file.open(filename, ios::out);
	//д�룺
	file << setw(10) << timetables[0].no;
	file << setw(10) << timetables[0].hour;
	file << setw(10) << timetables[0].minute;
	file << setw(10) << timetables[0].Starting_station;
	file << setw(10) << timetables[0].Last_station;
	file << setw(10) << timetables[0].time;
	file << setw(10) << timetables[0].fare;
	file << setw(10) << timetables[0].max_number;
	file << setw(10) << timetables[0].sold_number;

	for (int i = 1; i < n; i++)
	{
		cout.setf(ios::left);
		file << endl;
		file << setw(10) << timetables[i].no;
		file << setw(10) << timetables[i].hour;
		file << setw(10) << timetables[i].minute;
		file << setw(10) << timetables[i].Starting_station;
		file << setw(10) << timetables[i].Last_station;
		file << setw(10) << timetables[i].time;
		file << setw(10) << timetables[i].fare;
		file << setw(10) << timetables[i].max_number;
		file << setw(10) << timetables[i].sold_number;
	}
	return 0;
}


//5
void ShowBusInfo(Timetable* timetables, int n, int idx)
{
	if (idx > n)
	{
		cout << "������ʾ����";
		return;
	}
	else
	{
		cout.setf(ios::left);
		cout << setw(10) << timetables[idx].no;
		cout << timetables[idx].hour << ":";
		cout << setw(10) << timetables[idx].minute;
		cout << setw(10) << timetables[idx].Starting_station;
		cout << setw(10) << timetables[idx].Last_station;
		cout << setw(10) << timetables[idx].time;
		cout << setw(10) << timetables[idx].fare;
		cout << setw(15) << timetables[idx].max_number;
		cout << setw(10) << timetables[idx].sold_number << endl;
	}
}


//6
void ShowTimetable(Timetable* timetables, int n)
{
	OutPutBusList();
	for (int i = 0; i < n; i++)
		ShowBusInfo(timetables, n, i);
}


//7
void Query(Timetable* timetables, int n)
{
	char finding[64];//Ҫ��ѯ�ĳ��λ��յ�վ��
	int b[64];//�����±꣬����find����

	//ѡ���ѯ��ʽ��
	int choice;
	while (1)
	{
		cout << "��ѡ���ѯ��ʽ\n\n";
		cout << "1.���ճ��β�ѯ\n\n";
		cout << "2.�����յ�վ��ѯ\n\n";
		cout << "�������ѯ��ʽ��";
		cin >> choice;
		if (choice == 1 || choice == 2)
			break;
		system("cls");
		cout << "��ѯ����\n\n";
	}
	system("cls");

	int i; //ѭ������
	if (choice == 1)
	{
		cout << "������Ҫ��ѯ�ĳ��Σ�";
		cin >> finding;
		if (find(timetables, n, finding) == -1)
		{
			cout << "����ѯ�ĳ��β����ڣ�" << endl;
			return;
		}
		OutPutBusList();
		ShowBusInfo(timetables, n, find(timetables, n, finding));
	}
	else
	{
		cout << "������Ҫ��ѯ���յ�վ��";
		cin >> finding;
		if (find(timetables, n, finding, b) == -1)
		{
			cout << "����ѯ���յ�վ�����ڣ�" << endl;
			return;
		}
		OutPutBusList();
		for (i = 0; i < find(timetables, n, finding, b); i++)
			ShowBusInfo(timetables, n, b[i]);
	}
}


//8
int find(Timetable* timetables, int n, char* no)
{
	for (int i = 0; i < n; i++)
		if (!strcmp(no, timetables[i].no))
			return i;
	return -1;
}


//9
int find(Timetable* timetables, int n, char* Last_station, int* b)
{
	int no = 0; //������

	for (int i = 0; i < n; i++)
	{
		if (!strcmp(Last_station, timetables[i].Last_station))
		{
			b[no] = i;
			no++;
		}
	}

	if (no)
		return no;
	else
		return -1;
}


//10
int DelBus(Timetable* timetables, int n)
{
	char find_no[20];//Ҫע���ĳ���
	cout << "������Ҫע���ĳ���:";
	cin >> find_no;

	if (find(timetables, n, find_no) == -1)
	{
		cout << "�ó��β����ڻ��ѱ�ɾ��\n";
		return n;
	}

	for (int i = find(timetables, n, find_no); i < n; i++)
		timetables[i] = timetables[i + 1];
	return n - 1;
}


//11
void GenerateLogFileName(char* LogFileName)
{
	time_t t = time(0);
	struct tm* time;
	time = localtime(&t);

	char year[5], month[3], day[3];

	_itoa(time->tm_mday, day, 10);
	_itoa(time->tm_year + 1900, year, 10);
	_itoa(time->tm_mon + 1, month, 10);


	strcpy(LogFileName, year);
	strcat(LogFileName, "-");
	strcat(LogFileName, month);
	strcat(LogFileName, "-");
	strcat(LogFileName, day);
	strcat(LogFileName, ".log");
}


//12
int InitializationPassagerMode(Timetable* timetables, char* LogFileName, char* filename)
{
	int n;//��������
	int a = 0;

	fstream file_log;//��־�ļ�
	fstream file;//bus.txt
	file_log.open(LogFileName, ios::in);
	//��ʧ�ܣ�
	if (file_log.fail())
	{
		n = ReadFromFile(timetables, a, filename);
		for (int i = 0; i < n; i++)
			timetables[i].sold_number = 0;
		WritetoFile(timetables, n, LogFileName);
		return n;
	}
	//�򿪳ɹ���
	file_log.close();
	n = ReadFromFile(timetables, 0, LogFileName);

	return n;
}


//13
void TicketOrder(Timetable* timetables, int n)
{
	char find_no[20];//Ҫ����ĳ���
	int amount;//����

	cout << "������Ҫ����ĳ��Σ�";
	cin >> find_no;
	
	if (find(timetables, n, find_no) == -1)
	{
		cout << "δ�ҵ����Σ�����飡" << endl;
		return;
	}

	if (StopSevice(timetables, n, find_no))
	{
		cout << "��Ʊʧ�ܣ�[ERROR:���κż����������Ѿ�����]" << endl;
		return;
	}

	cout << "�����빺Ʊ��Ŀ��";
	cin >> amount;

	if ((timetables[find(timetables, n, find_no)].max_number - timetables[find(timetables, n, find_no)].sold_number) < amount)
	{
		cout << "��Ʊ���㣡" << endl;
		return;
	}

	timetables[find(timetables, n, find_no)].sold_number += amount;
	cout << "��Ʊ�ɹ���\n";
}


//14
void TicketDelete(Timetable* timetables, int n)
{
	char find_no[20];//Ҫ�˵ĳ���
	int amount;//��Ʊ����

	cout << "������Ҫ��Ʊ�ĳ��Σ�";
	cin >> find_no;

	if (find(timetables, n, find_no) == -1)
	{
		cout << "δ�ҵ����Σ�����飡" << endl;
		return;
	}

	if (StopSevice(timetables, n, find_no))
	{
		cout << "��Ʊʧ�ܣ�[ERROR:���κż����������Ѿ�����]" << endl;
		return;
	}

	cout << "������Ҫ��Ʊ��Ŀ��";
	cin >> amount;

	if (timetables[find(timetables, n, find_no)].sold_number < amount)
	{
		cout << "��û����ô��" << endl;
		return;
	}

	timetables[find(timetables, n, find_no)].sold_number -= amount;
	cout << "��Ʊ�ɹ���\n";
}


//15
//�̲�����
int StopSevice(Timetable* timetables, int n, char* no)
{
	struct tm* local;
	time_t t;
	t = time(NULL);
	local = localtime(&t);
	int i = find(timetables, n, no);
	if ((local->tm_hour * 60 + local->tm_min) + 10 < timetables[i].hour * 60 + timetables[i].minute)
		return 0;
	return 1;
}


//16
void SortbyTime(Timetable* timetables, int n)
{
	int i, j;
	Timetable temp;
	if (n > 0)
		for (i = 0; i < n - 1; i++)
		{
			for (j = 0; j < n - 1 - i; j++)
			{
				if (timetables[j].hour * 60 + timetables[j].minute > timetables[j + 1].hour * 60 + timetables[j + 1].minute)
				{
					temp = timetables[j + 1];
					timetables[j + 1] = timetables[j];
					timetables[j] = temp;
				}
			}
		}
}


//17
int Quit()
{
	char choice;//ѡ��
	cout << "�˳�ϵͳ��(y)\n";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
		return 1;
	return 0;
}


//�˵���
void OutPutBusList()
{
	cout.setf(ios::left);
	cout << setw(10) << "���κ�";
	cout << setw(10) << "����ʱ��";
	cout << "  ";
	cout << setw(10) << "ʼ��վ";
	cout << setw(10) << "�յ�վ";
	cout << setw(10) << "Ԥ����ʱ";
	cout << setw(10) << "Ʊ��";
	cout << setw(15) << "����ؿ���";
	cout << setw(10) << "����Ʊ��" << endl;
}
