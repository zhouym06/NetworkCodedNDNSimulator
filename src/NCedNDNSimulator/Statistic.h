
#ifndef __STATISTIC_H__
#define __STATISTIC_H__



class Statistic{
	static int content_num;
	//static int routerNum;

	static int total_cache_hit;
	static int total_cache_miss;
	static int total_request;
	static int total_networkload;
	static int total_server_load;

	static int* cache_hit_count;
	static int* cache_miss_count;
	static int* request_count;
	static int* server_load;

public:
	Statistic(){;}
	~Statistic();

	static void Init(int content_num);
	static void CountRequest(int content_num);
	static void CountHit(int content_num);
	static void CountMiss(int content_num);
	static void CountServerLoad(int content_num);
	static void CountNetworkLoad();
	

	static void Display();

	
	
};

#endif
