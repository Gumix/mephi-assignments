#include "stdafx.h"
#include "lab9.h"

unsigned long factorial(unsigned long n)
{
	if (1 < n) return n * factorial(n-1);
	return 1;
}

void Bezier3(int *bx, int *by, int *x, int *y, double t)
{
	double B[4];

	for (int i = 0; i <= 3; i++)
		B[i] = factorial(3) / factorial(i) / factorial(3-i) * pow(t, i) * pow(1-t, 3-i);

	for (int i = 0; i <= 3; i++)
		*x += B[i] * bx[i],
		*y += B[i] * by[i];
}
