#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>

using namespace std;

int main()
{
	cout.precision(3);
	cout.setf(ios::right);
	double x;
	ofstream out;
	out.open("table.txt");
	out << setw(8) << "Number" << setw(8) << "Square" << setw(12) << "Square root" << endl;
	for (x = 1; x <= 100; x++)
		out << setw(8) << x << setw(8) << x * x << setw(8) << sqrt(x) << endl;
	out.close();
	return 0;
}