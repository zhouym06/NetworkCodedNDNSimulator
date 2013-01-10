
#include "RequestsGenerator.h"
#include "MyRandom.h"
#include "Logger.h"
#include "Common.h"



double* RequestsGenerator::cdf;		//Cumulative distribution function by power law//sorted by popularity
int RequestsGenerator::max_content_num;

RequestsGenerator::RequestsGenerator()
{
	RequestsGenerator::cdf = NULL;
	RequestsGenerator::max_content_num = 0;
}

Requests* RequestsGenerator::GenUniformRequests(int request_num, int content_num)
{
	Requests* r = new Requests(request_num);
	max_content_num = content_num;
	
	int c_no;
	double time = 0;
	// Hit of contentNo is distributed  Evenly
	
	for (int i = 0; i < request_num; i++) {
		
		c_no = (int) (max_content_num * MyRandom::NextDouble());
		Logger::Log(LOGGER_DEBUG) << "RequestsGenerator::GenUniformRequests() requesting" << c_no << "" << std::endl;
		time += MyRandom::NextPoisson(1) / 10; 
		r->Set(new Request(c_no, time), i);
	}
	r->Sort();
	return r;
}

Requests* RequestsGenerator::GenPoissonRequests(int request_num, int content_num)
{
	Requests* r = new Requests(request_num);
	max_content_num = content_num;
	InitCDF();
	
	int c_no;
	double time = 0;
	// ContentName as prefix-contentNo i.e. ServerNo-ContentNo-SliceNo
	// Hit of contentNo is distributed by power law
	
	for (int i = 0; i < request_num; i++) {
		c_no = (int) (GetContentNo(MyRandom::NextDouble()));
		Logger::Log(LOGGER_DEBUG) << "RequestsGenerator::GenUniformRequests() requesting" << c_no << "" << std::endl;

		// 10 request is generated each second?
		time += MyRandom::NextPoisson(1) / 10; 
		r->Set(new Request(c_no, time), i);
		//Logger.log("RequestGenerator:genPoissonRequests(" + i + ")" + "to\tContent" + cNo + "\tat " + time, Logger.DETAIL);
	}
	r->Sort();
	return r;
}

void RequestsGenerator::InitCDF()
{
	cdf = new double[max_content_num];
	//Cumulative distribution function by power law
	double sum = 0;
	for(int i = 0; i < max_content_num; i++)	//a Harmonic series 
	{
		sum += 1/ ((double)i + 1);
	}
	cdf[0] = 1/ sum;
	sum = cdf[0];
	for(int i = 1; i < max_content_num; i++)
	{
		cdf[i] =  cdf[i - 1] + cdf[0] / (i + 1);
		sum += cdf[0] / (i + 1);
	}
}

int RequestsGenerator::GetContentNo(double rank)//by binary search
{
	int result = GetContentNo(rank, 0, max_content_num);
	return result;		
}

int RequestsGenerator::GetContentNo(double p, int begin, int end)
{
	if(begin == end)
		return begin;
	if(begin == end - 1)
	{
		return p < cdf[begin] ? begin : end;
	}
	int mid = (int) (begin + ((double) (end - begin)) * 0.3);
	mid = mid == begin ? begin + 1 : mid;
	return p < cdf[mid] ? GetContentNo(p, begin, mid) : GetContentNo(p, mid, end);
}

