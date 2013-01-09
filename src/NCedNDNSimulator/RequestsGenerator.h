#ifndef __REQUESTS_GENERATOR_H__
#define __REQUESTS_GENERATOR_H__

#include "Requests.h"

class RequestsGenerator{
	static double* cdf;		//Cumulative distribution function by power law//sorted by popularity
	static int max_content_num;

	static void InitCDF();
	static int GetContentNo(double);
	static int GetContentNo(double, int, int);
public:
	RequestsGenerator();
	~RequestsGenerator(){delete cdf;}
	static Requests* GenPoissonRequests(int,int);
	static Requests* GenUniformRequests(int,int);

};

#endif