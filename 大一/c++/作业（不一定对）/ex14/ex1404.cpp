#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	fstream in1, in2, out;
	in1.open("w1.txt", ios::in);
	if (!in1)
	{
		cout << "Can not open w1.txt!" << endl;
		exit(1);
	}
	in2.open("w2.txt", ios::in);
	if (!in2)
	{
		cout << "Can not open w2.txt!" << endl;
		exit(2);
	}
	out.open("result.txt", ios::out);
	if (!out)
	{
		cout << "Can not open result.txt!" << endl;
		exit(3);
	}
	int i = 0, j = 0, a1[1024], a2[1024], b[1024], ii, jj, k, state;
	while (in1 >> a1[i])i++;
	while (in2 >> a2[j])j++;
	for (ii = 0, jj = 0, k = 0; ii < i && jj < j;)
	{
		if (a1[ii] > a2[jj])
			b[k++] = a1[ii++];
		else
			b[k++] = a2[jj++];
		if (ii == i)state = 0;
		else if (jj == j)state = 1;
	}
	
	if (state)
		while (ii < i)
			b[k++] = a1[ii++];
	else
		while (jj < j)
			b[k++] = a2[jj++];

	for (i = 0; i < k; i++)
		out << b[i];


	in1.close();
	in2.close();
	out.close();
	return 0;
}