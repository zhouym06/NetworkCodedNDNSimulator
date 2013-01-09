
#ifndef __REQUESTS_H__
#define __REQUESTS_H__

#include "Request.h"

class Requests{
	int req_num;
	Request** reqs;


public:
	Requests(){;}
	Requests(int);
	~Requests();
	void Set(Request*, int);
	void Sort();
	Request** GetReqs();
	int GetRNum();


	
};

#endif
