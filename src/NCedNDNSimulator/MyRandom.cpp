
#include "MyRandom.h"

#include <stdio.h> 
#include <iostream> 
#include <time.h> 
#include <math.h>

bool MyRandom::inited;

double MyRandom::NextDouble()
{
	if(!inited)
	{
		srand( (unsigned)time( NULL ) );
		inited = true;
	}
	return (double)rand() / RAND_MAX;
}
	
double MyRandom::NextPoisson(double lamda) 
{
	double x = 0, b = 1, c = exp(-lamda), u;
	do {
		u = NextDouble();
		b *= u;
		if (b >= c)
			x++;
	} while (b >= c);
	if (x == 0)
		return 0.01;
	return x;
}

double MyRandom::NextExp(double lamda) 
{
	double z = NextDouble();
	double x = -(1 / lamda) * log(z);
	return x;
}