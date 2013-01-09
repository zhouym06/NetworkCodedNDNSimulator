
#include "Requests.h"
#include "Common.h"
#include "Logger.h"
#include <algorithm>

Requests::Requests(int request_num){ 
	req_num = request_num;
	reqs = new Request*[request_num];
}
Requests::~Requests()
{
	if(reqs != NULL)
	{
		delete[] reqs;
	}
}

void Requests::Sort()
{
	//Collections.sort(reqs);
	//qsort(reqs, rNum, sizeof(Request), compare);
	std::sort(reqs,reqs + req_num);
}


void Requests::Set(Request* new_req, int index)
{
	if(reqs == NULL)
	{
		return;
	}
	if(index > req_num)
	{
		return;
	}
	reqs[index] = new_req;
	Logger::Log(LOGGER_DEBUG) << "Requests::Set()  Reqeust of Content " << (new_req->GetContentNo()) << " is set." << std::endl;
}

Request** Requests::GetReqs()
{
	return reqs;
}
int Requests::GetRNum()
{
	return req_num;
}


