#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	char filename[40], line[80];
	ifstream infile;
	cout << "请输入文件名：";
	cin >> filename;
	infile.open(filename);
	if (!infile)
	{
		cout << "can not open file:" << filename << endl;
		exit(1);
	}
	while (infile.getline(line, 80))
		cout << line << endl;
	infile.close();
	return 0;
}