#include <iostream>
using namespace std;
int main()
{
	char x;
	cout << "ÇëÊäÈë¿¼ºËµÈ¼¶" << endl;
	cin >> x;
	if (x == 'a' || x == 'A')  cout << "90-100" << endl;
	else if (x == 'b' || x == 'B')  cout << "80-89" << endl;
	else if (x == 'c' || x == 'C')  cout << "70-79" << endl;
	else if (x == 'd' || x == 'D')  cout << "60-69" << endl;
	else if (x == 'e' || x == 'E')  cout << "0-59" << endl;
	else  cout << "error" << endl;
	return 0;
}