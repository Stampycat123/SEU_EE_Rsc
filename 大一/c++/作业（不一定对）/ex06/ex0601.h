#pragma once
int pow(int x, int y)
{
	double u = x;
	x = 1;
	for (int i = 1; i <= y; i++)
	{
		x *= u;
	}
	return x;
}