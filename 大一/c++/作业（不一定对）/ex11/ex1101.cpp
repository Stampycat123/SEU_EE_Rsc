#include<iostream>
#include<iomanip>
using namespace std;

class Time
{
	int hour, minute, second;
	static int baseHour, baseMinute, baseSecond;

	static int timeToSecond(Time t)
	{
		int tSecond;
		tSecond = t.hour * 60 * 60 + t.minute * 60 + t.second;
		return tSecond;
	}

public:
	Time(int h= 0, int m= 0, int s= 0)
	{
		hour = h;
		minute = m;
		second = s;
	}

	static int timeBaseDiffence(Time t)
	{
		int differ;
		int t0toSecond = baseHour * 60 * 60 + baseMinute * 60 + baseSecond;
		differ = timeToSecond(t) - t0toSecond;
		return differ;
	}

	void show()
	{
		cout << hour << ":" << minute << ":" << second << endl;
	}

	friend int diffence(Time t1, Time t2)
	{
		int t;
		t = timeToSecond(t1) - timeToSecond(t2);
		return t;
	}
};

int Time::baseHour = 1;
int Time::baseMinute = 10;
int Time::baseSecond = 10;

int main()
{
	Time t1(1, 11, 2), t2(1, 12, 50);
	t1.show();
	t2.show();
	cout << "t1与基准时间之差：" << t1.timeBaseDiffence(t1) << "s" << endl;
	cout << "t2与基准时间之差：" << t2.timeBaseDiffence(t2) << "s" << endl;
	cout << "t1与t2时间之差：" << diffence(t1, t2) << "s" << endl;
	return 0;
}
