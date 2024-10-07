#include<iostream>
using namespace std;

class String
{
	char* str;
	int len;
public:
	String(char* s = NULL)
	{
		len = strlen(s);
		str = new char[len + 1];
		if (s && *s)
		{
			strcpy_s(str, len, s);
			str[len] = '\0';
		}
		else
			*str = '\0';
	}

	String(String& s)
	{
		len = s.len;
		if (s.str && *s.str)
		{
			str = new char[s.len + 1];
			strcpy_s(str, s.len, s.str);
			str[len] = '\0';
		}
		else
			*str = '\0';
	}

	~String()
	{
		if (str)
			delete[] str;
	}

	void set(char* s)
	{
		if (str)
		{
			delete[] str;
		}
		len = strlen(s);
		str = new char[len + 1];
		if (s && *s)
		{
			strcpy_s(str, len, s);
			str[len] = '\0';
		}
		else
			*str = '\0';
	}

	void show()
	{
		if (str)
			cout << str << endl;
		else
			cout << "×Ö·û´®Îª¿Õ£¡" << endl;
	}

	int getLen()
	{
		return len;
	}

	void delChar(char c)
	{
		if (!str)
			return;
		char* newStr = new char[len + 1];
		int newLen = 0, i = 0;
		while (i < len)
		{
			if (*(str + i) != c)
				newStr[newLen++] = *str;
			i++;
		}
		newStr[newLen] = '\0';
		delete[] str;
		len = newLen;
		str = newStr;
	}

	String& operator = (String& );
	String& operator+=(String&);
	bool operator==(String&);
	friend String operator+(String&, String&);
};

String& String::operator=(String& s)
{
	len = s.len;
	if (str)
		delete str;
	str = new char[len + 1];
	if (s.str)
	{
		strcpy_s(str, len, s.str);
		str[len] = '\0';
	}
	else
		*str = '\0';

	return*this;
}

String& String::operator+=(String& s)
{
	char* newStr = new char[len + s.len + 1];
	strcpy_s(newStr, len, this->str);
	strcpy_s(newStr + len, s.len, s.str);
	newStr[len + s.len] = '\0';
	delete str;
	len = strlen(newStr);
	str = newStr;
	return*this;
}

bool String::operator==(String& s)
{
	if (str && s.str)
		if (len == s.len)
			return !strcmp(str, s.str);
	return false;
}

String operator+(String& s1, String& s2)
{
	String s(s1);
	s.operator+=(s2);
	return s;
}

int main()
{
	cout << "ÊäÈëÒ»¸ö×Ö·û´®£º" << endl;
	char* s = new char;
	cin >> s;
	String S1(s);
	cout << "S1:";
	S1.show();

	delete s;
	cout << "ÊäÈëÒ»¸ö×Ö·û´®£º" << endl;
	s = new char;
	cin >> s;
	String S2(s);
	cout << "S2:";
	S2.show();

	S1 += S2;
	S1.show();

	cout << "ÊäÈëÐèÒªÉ¾³ýµÄ×Ö·û£º\n";
	char c;
	cin >> c;
	S1.delChar(c);
	S1.show();
}