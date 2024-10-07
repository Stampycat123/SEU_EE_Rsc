#include <iostream>
using namespace std;
int main()
{
	char grade;
	cout << "ÇëÊäÈë¿¼ºËµÈ¼¶" << endl;
	cin >> grade;
	switch (grade)
	{
	case'a':cout << "90-100" << endl; break;
	case'A':cout << "90-100" << endl; break;
	case'b':cout << "80-89" << endl; break;
	case'B':cout << "80-89" << endl; break;
	case'c':cout << "70-79" << endl; break;
	case'C':cout << "70-79" << endl; break;
	case'd': cout << "60-69" << endl; break;
	case'D': cout << "60-69" << endl; break;
	case'e':cout << "0-59" << endl; break;
	case'E':cout << "0-59" << endl; break;
	default:cout << "error" << endl;
	}
	return 0;
}