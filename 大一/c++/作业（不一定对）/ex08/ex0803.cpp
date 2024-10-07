#include <iostream>
#include <iomanip>
using namespace std;

enum color { RED, GREEN, BLUE };
void print(color c)
{
	switch (c)
	{
	case RED:cout << setw(10) << "RED"; break;
	case GREEN:cout << setw(10) << "GREEN"; break;
	case BLUE:cout << setw(10) << "BLUE"; break;
	default:break;
	}
}

int main()
{
	int count = 0;
	color i, j, k;
	for(i=RED;i<=BLUE;i=color(int(i)+1))
		for(j = RED; j <= BLUE; j = color(int(j) + 1))
			if(i!=j)
				for(k = RED; k <= BLUE; k = color(int(k) + 1))
					if (k != i && k != j)
					{
						cout << setw(10) << ++count;
						print(i);
						print(j);
						print(k);
						cout << endl;
					}
	return 0;
}