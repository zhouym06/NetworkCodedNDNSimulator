
#include "Statistic.h"
#include "Common.h"
#include "Logger.h"

#include <string>

int Statistic::content_num;

int Statistic::total_cache_hit;
int Statistic::total_cache_miss;
int Statistic::total_request;
int Statistic::total_networkload;
int Statistic::total_server_load;

int* Statistic::cache_hit_count = NULL;
int* Statistic::cache_miss_count = NULL;
int* Statistic::request_count = NULL;
int* Statistic::server_load = NULL;

void Statistic::Init(int c_num)
{
	Logger::Log(LOGGER_INFO) << "Statistic::Init(" << c_num << ")" << std::endl;
	content_num			= c_num;
	total_cache_hit		= 0;
	total_cache_miss	= 0;
	total_request		= 0;
	total_networkload	= 0;
	total_server_load	= 0;

	if(cache_hit_count != NULL)
		delete[] cache_hit_count;
	if(cache_miss_count != NULL)
		delete[] cache_miss_count;
	if(request_count != NULL)
		delete[] request_count;
	if(server_load != NULL)
		delete[] server_load;

	cache_hit_count		= new int [content_num];
	memset(cache_hit_count, 0, content_num * sizeof(int));
	cache_miss_count	= new int [content_num];
	memset(cache_miss_count, 0, content_num * sizeof(int));
	request_count		= new int [content_num];
	memset(request_count, 0, content_num);
	server_load			= new int [content_num];
	memset(server_load, 0, content_num * sizeof(int));

	Logger::Log() << "Statistic::Init() fin." << std::endl;
}

void Statistic::CountRequest(int cNo)
{
	total_request++;
	request_count[cNo]++;
}
void Statistic::CountHit(int cNo)
{
	total_cache_hit++;
	cache_hit_count[cNo]++;
}
void Statistic::CountMiss(int cNo)
{
	total_cache_miss++;
	cache_miss_count[cNo]++;
}
void Statistic::CountServerLoad(int cNo)
{
	total_server_load++;
	server_load[cNo]++;
}

void Statistic::CountNetworkLoad()
{
	total_networkload++;
}


void Statistic::Display()
{
	Logger::Log(LOGGER_INFO) << "Statistic::Display()" << std::endl;
	Logger::Log() << "total_cache_miss:\t" 
		<< (double)total_cache_miss / (double)(total_cache_miss + total_cache_hit)
		<<  "\t" << total_cache_miss << std::endl;
	Logger::Log() << "total_cache_hit:\t" 
		<< (double)total_cache_hit / (double)(total_cache_miss + total_cache_hit)
		<<  "\t" << total_cache_hit << std::endl;

	Logger::Log() << "total_request:\t" << total_request << std::endl;
	Logger::Log() << "total_networkload:\t" << total_networkload << std::endl;
	Logger::Log() << "total_server_load:\t" << total_server_load << std::endl;

	Logger::Log() << "Statistic::Display() fin." << std::endl;
}