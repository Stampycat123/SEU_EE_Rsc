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
	char no[16];//为什么教材是char类型？
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


//-------------------------------------------------------函数声明：-----------------------------------------------------
//各级菜单函数
	void AdminMode(Timetable * timetables, char* filename);
	void PassagerMode(Timetable * timetables, char* filename);
	int MainWindowSelect();
	int AdminWindowSelect();
	int PassagerWindowSelect();
	//菜单功能处理函数
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


//-------------------------------------------------主函数：------------------------------------------------------
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


//------------------------------------------------菜单函数：--------------------------------------------------
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
	const char* m[4] = { "1.管理员登录",
		"2.普通顾客登录",
		"3.退出" };
	int i, choice;
	do {
		system("cls");
		for (i = 0; m[i]; i++)
			cout << m[i] << endl;
		cout << "请输入选择：";
		cin >> choice;//此处如何让输入a时不出错？
	} while (choice < 1 || choice>3);
	return(choice);
}


int AdminWindowSelect()
{
	const char* am[6] = { "1.增加车次信息","2.查看所有车次信息","3.车辆信息查询","4.注销车次","5.退出"};
	int choice;
	do {
		system("cls");
		for (int i = 0; am[i]; i++)
			cout << am[i] << endl;
		cout << "请输入选择：";
		cin >> choice;
	} while (choice < 1 || choice>5);
	return(choice);
}


int PassagerWindowSelect()
{
	const char* pm[5] = { "1.车辆信息查询","2.购买车票","3.退票","4.退出" };
	int choice;
	do {
		system("cls");
		for (int i = 0; i < 4; i++)
			cout << pm[i] << endl;
		cout << "请输入选择：";
		cin >> choice;
	} while (choice < 1 || choice>4);
	return(choice);
}


//1
//?不会写
//void Signin()
//{
//	int i, j;
//	char name[16] = { '\0' };
//loop:	char password[32] = { '\0' };
//	cout << "请输入用户名：";
//	cin >> name;
//	cin.ignore();//不读入换行符
//	if (!strcmp(name ,"admin"))
//	{
//		cout << "\n请输入密码：";
//		system("cls");
//
//		i = 0;
//		cout << "请输入用户名：";
//		cout << name << endl;
//		cout << "\n请输入密码：";
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
//			cout << "登录成功！正在进入管理员窗口" << endl;
//		}
//		else
//		{
//			cout << "输入的用户名或密码有误" << endl;
//			goto loop;
//		}
//	}
//	else
//	{
//		cout << "用户不存在！" << endl;
//		goto loop;
//	}
//}


//------------------------------------------------------功能函数：------------------------------------------------
//1
void Signin()
{
	int i;//用来循环输入密码便于隐藏
	int j = 0;
	char account[32];


	while (1)
	{
		char password[64] = { '\0' };//密码

		cout << "欢迎使用汽车站车票管理系统\n\n";
		cout << "账号：";
		cin >> account;//账号
		cin.ignore();//不提取换行符
		cout << "\n密码：";
		system("cls");

		//隐藏密码（重复清屏）：
		i = 0;
		while (1)
		{
			cout << "欢迎使用汽车站车票管理系统\n\n";
			cout << "账号：";
			cout << account << endl;
			cout << endl;
			cout << "密码：";

			for (j = 0; j < i; j++)
				cout << "*";

			password[i] = _getch();

			if (password[i] == '\r')
				break;

			//输入backspace删除*：
			if (password[i] == '\b')
			{
				password[i] = '\0';
				i--;

				//未输入状态下（输入0个密码字符时）按backspace不会出错：
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
		cout << "输入的账号或密码有误\n";

		system("pause");
		system("cls");
	}
}


//2
int ReadFromFile(Timetable* timetables, int n, char* filename)
{
	fstream file;
	file.open(filename, ios::in);
	//找不到文件时：
	if (file.fail())
	{
		cout << "文件不存在！\n\n";
		exit(1);
	}
	//找到文件：
	while (!file.eof())
	{
		//----------------------------------------------------进入循环体后此处开始有误，但不知为何
		//---------------------------------------------------错误已更正
		file >> timetables[n].no;
		//防止第一行是空的被读取进去：
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
	int i, state;//state判断车次是否已存在，状态0代表未发现重复

	while(1)
	{
		state = 0;
		cout << "\n\n请输入车次号:";
		cin >> timetables[n].no;
		cout << endl;
		//寻找重复车次
		for (i = 0; i < n; i++)
			if (!strcmp(timetables[i].no, timetables[n].no))
				state = 1;

		if (!state)
			break;
		else
			cout << "已存在相同车次";
	}

	cout << "请输入出发时间（小时）：";
	cin >> timetables[n].hour;
	cout << endl;
	cout << "请输入出发时间（分钟）：";
	cin >> timetables[n].minute;
	cout << endl;
	cout << "请输入起始站：";
	cin >> timetables[n].Starting_station;
	cout << endl;
	cout << "请输入终点站：";
	cin >> timetables[n].Last_station;
	cout << endl;
	cout << "请输入大致行车时间：";
	cin >> timetables[n].time;
	cout << endl;
	cout << "请输入票价：";//为何书上没有要求输入票价？
	cin >> timetables[n].fare;
	cout << endl;
	cout << "请输入额定载客量：";
	cin >> timetables[n].max_number;
	timetables[n].sold_number = 0;//已售票数为0
	n++;

	return n;
}


//4
int WritetoFile(Timetable* timetables, int n, char* filename)
{
	if (n == 0)
		return 0;//先判断是否需要写入
	fstream file;//文件
	SortbyTime(timetables, n);//排序

	file.open(filename, ios::out);
	//写入：
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
		cout << "车次显示错误！";
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
	char finding[64];//要查询的车次或终点站名
	int b[64];//储存下标，用于find函数

	//选择查询方式：
	int choice;
	while (1)
	{
		cout << "请选择查询方式\n\n";
		cout << "1.按照车次查询\n\n";
		cout << "2.按照终点站查询\n\n";
		cout << "请输入查询方式：";
		cin >> choice;
		if (choice == 1 || choice == 2)
			break;
		system("cls");
		cout << "查询错误！\n\n";
	}
	system("cls");

	int i; //循环变量
	if (choice == 1)
	{
		cout << "请输入要查询的车次：";
		cin >> finding;
		if (find(timetables, n, finding) == -1)
		{
			cout << "所查询的车次不存在！" << endl;
			return;
		}
		OutPutBusList();
		ShowBusInfo(timetables, n, find(timetables, n, finding));
	}
	else
	{
		cout << "请输入要查询的终点站：";
		cin >> finding;
		if (find(timetables, n, finding, b) == -1)
		{
			cout << "所查询的终点站不存在！" << endl;
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
	int no = 0; //车次数

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
	char find_no[20];//要注销的车次
	cout << "请输入要注销的车次:";
	cin >> find_no;

	if (find(timetables, n, find_no) == -1)
	{
		cout << "该车次不存在或已被删除\n";
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
	int n;//车次数量
	int a = 0;

	fstream file_log;//日志文件
	fstream file;//bus.txt
	file_log.open(LogFileName, ios::in);
	//打开失败：
	if (file_log.fail())
	{
		n = ReadFromFile(timetables, a, filename);
		for (int i = 0; i < n; i++)
			timetables[i].sold_number = 0;
		WritetoFile(timetables, n, LogFileName);
		return n;
	}
	//打开成功：
	file_log.close();
	n = ReadFromFile(timetables, 0, LogFileName);

	return n;
}


//13
void TicketOrder(Timetable* timetables, int n)
{
	char find_no[20];//要购买的车次
	int amount;//数量

	cout << "请输入要购买的车次：";
	cin >> find_no;
	
	if (find(timetables, n, find_no) == -1)
	{
		cout << "未找到车次！请核验！" << endl;
		return;
	}

	if (StopSevice(timetables, n, find_no))
	{
		cout << "购票失败！[ERROR:车次号即将发车或已经发车]" << endl;
		return;
	}

	cout << "请输入购票数目：";
	cin >> amount;

	if ((timetables[find(timetables, n, find_no)].max_number - timetables[find(timetables, n, find_no)].sold_number) < amount)
	{
		cout << "余票不足！" << endl;
		return;
	}

	timetables[find(timetables, n, find_no)].sold_number += amount;
	cout << "购票成功！\n";
}


//14
void TicketDelete(Timetable* timetables, int n)
{
	char find_no[20];//要退的车次
	int amount;//退票数量

	cout << "请输入要退票的车次：";
	cin >> find_no;

	if (find(timetables, n, find_no) == -1)
	{
		cout << "未找到车次！请核验！" << endl;
		return;
	}

	if (StopSevice(timetables, n, find_no))
	{
		cout << "退票失败！[ERROR:车次号即将发车或已经发车]" << endl;
		return;
	}

	cout << "请输入要退票数目：";
	cin >> amount;

	if (timetables[find(timetables, n, find_no)].sold_number < amount)
	{
		cout << "你没买那么多" << endl;
		return;
	}

	timetables[find(timetables, n, find_no)].sold_number -= amount;
	cout << "退票成功！\n";
}


//15
//教材样例
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
	char choice;//选项
	cout << "退出系统？(y)\n";
	cin >> choice;

	if (choice == 'Y' || choice == 'y')
		return 1;
	return 0;
}


//菜单栏
void OutPutBusList()
{
	cout.setf(ios::left);
	cout << setw(10) << "车次号";
	cout << setw(10) << "发车时间";
	cout << "  ";
	cout << setw(10) << "始发站";
	cout << setw(10) << "终点站";
	cout << setw(10) << "预计用时";
	cout << setw(10) << "票价";
	cout << setw(15) << "最大载客量";
	cout << setw(10) << "已售票数" << endl;
}
