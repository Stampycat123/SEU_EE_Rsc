#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

int main()
{
	char infilename[40], outfilename[40], ch;
	cout << "请输入待复制文件名：";
	cin >> infilename;
	ifstream infile(infilename, ios::in);
	if (!infile)
	{
		cout << "can not open file:" << infilename << endl;
		exit(1);
	}
	cout << "请输入目标文件名：";
	cin >> outfilename;
	ofstream outfile(outfilename, ios::out);
	if (!outfile)
	{
		cout << "can not open file:" << outfilename << endl;
		exit(2);
	}
	while (infile.get(ch))
		outfile << ch;
	infile.close();
	outfile.close();
	return 0;
}