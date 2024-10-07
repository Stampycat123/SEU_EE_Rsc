#include<iostream>
using namespace std;

class Date
{
	int year, month, day;
public:
	Date(int y = 2023, int m = 3, int d = 9)
	{
		year = y;
		month = m;
		day = d;
	}

	void getYMD(int* y, int* m, int* d)
	{
		y = &year;
		m = &month;
		d = &day;
	}

	void getYMD(int& y, int& m, int& d)
	{
		y = year;
		m = month;
		d = day;
	}

	bool leapYear()
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		return false;
	}

	bool dayTrue()
	{
		if (month <= 0 || day <= 0 || month > 12 || day > 31)
			return false;
		if (leapYear() && month == 2 && day > 29)
			return false;
		if (!(leapYear()) && month == 2 && day > 28)
			return false;
		if (!(leapYear()) && (month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
			return false;
		if (!(leapYear()) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
			return false;
		return true;
	}

	void increaseDay()
	{
		if (dayTrue())
		{
			if (month == 2)
			{
				if (leapYear())
				{
					if (day == 29)
					{
						day = 1;
						if (month == 12)
						{
							month = 1;
							year += 1;
						}
						else
							month += 1;
					}
					else
						day += 1;
				}
				else
				{
					if (day == 28)
					{
						day = 1;
						if (month == 12)
						{
							month = 1;
							year += 1;
						}
						else
							month += 1;
					}
					else
						day += 1;
				}
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day == 30)
				{
					day = 1;
					if (month == 12)
					{
						month = 1;
						year += 1;
					}
					else
						month += 1;
				}
				else
					day += 1;
			}
			else if (month <= 12)
			{
				if (day == 31)
				{
					day = 1;
					if (month == 12)
					{
						month = 1;
						year += 1;
					}
					else
						month += 1;
				}
				else
					day += 1;
			}
		}
		else
			cout << "日期不存在,无法补全下一天！" << endl;
	}

	void show()
	{
		if (dayTrue())
			cout << year << "/" << month << "/" << day << endl;
		else
			cout << "日期不存在！" << endl;
	}
};

int main()
{
	Date date(2023);
	/*int y, m, d;
	cout << "请分别输入正确的年、月、日：" << endl;
	cin >> y >> m >> d;*/

	date.show();

	date.increaseDay();
	date.show();

	return 0;
}