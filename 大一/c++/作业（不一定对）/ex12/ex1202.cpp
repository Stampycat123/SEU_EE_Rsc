#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

void _itoa(int n, int fixlen, char* s)
{
	int i, j, t;
	for (i = 0; n; n = n / 10, i++)
		s[i] = n % 10 + '0';
	for (; i < fixlen; i++)
		s[i] = 0;
	s[i] = '\0';
	for (j = 0; j < i / 2; j++)
	{
		t = s[j];
		s[j] = s[i - 1 - j];
		s[i - 1 - j] = t;
	}
}

class Date
{
	int year, month, day;
public:
	Date(int y, int m, int d)
	{
		year = y; month = m; day = d;
	}

	void setDate(int y, int m, int d)
	{
		year = y; month = m; day = d;
	}

	void getDate(char* date)
	{
		char* y, * m, * d;
		y = new char;
		m = new char;
		d = new char;
		_itoa(year, y, 4);
		_itoa(month, m, 2);
		_itoa(day, d, 2);
		strcat(date, y);
		strcat(date+4, "/");
		strcat(date+5, m);
		strcat(date+7, "/");
		strcat(date+8, d);
	}
};

class Time
{
	int hour, minute, second;
public:
	Time(int h, int m, int s)
	{
		hour = h; minute = m; second = s;
	}

	void setTime(int h, int m, int s)
	{
		hour = h; minute = m; second = s;
	}

	void getTime(char*time)
	{
		char* h, * m, * s;
		h = new char;
		m = new char;
		s = new char;
			_itoa(hour, h,2);
			_itoa(minute, m,2);
			_itoa(second, s,2);
		strcat(time, h);
		strcat(time, ":");
		strcat(time, m);
		strcat(time, ":");
		strcat(time, s);
	}
};

class DateTime :public Date, public Time
{
public:
	DateTime(int y, int mo, int d, int h, int mi, int s) :Date(y, mo, d), Time(h, mi, s)
	{}

	void setDateTime(int y, int mo, int d, int h, int mi, int s)
	{
		setTime(h, mi, s);
		setDate(y, mo, d);
	}

	void getDateTime(char* dt)
	{
		char* date, * time;
		date = new char;
		time = new char;
		getDate(date);
		getTime(time);
		strcat(dt, date);
		strcat(dt+10, " ");
		strcat(dt+11, time);
	}
};

int main()
{
	char* dt;
	dt = new char;
	int y, mo, d, h, mi, s;
	cout << "请分别输入年月日：" << endl;
	cin >> y >> mo >> d;
	cout << "请分别输入时分秒：" << endl;
	cin >> h >> mi >> s;
	
	DateTime datetime(y, mo, d, h, mi, s);
	datetime.getDateTime(dt);
	cout << "日期：";
	cout << dt;

	return 0;
}