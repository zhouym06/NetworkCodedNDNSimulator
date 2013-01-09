#ifndef __MY_RANDOM_H__
#define __MY_RANDOM_H__

class MyRandom
{
	static bool inited;
public:
	MyRandom(){inited = false;}

	static double NextDouble();
	static double NextPoisson(double);
	static double NextExp(double);

};

#endif

