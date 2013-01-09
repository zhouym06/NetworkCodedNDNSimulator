
#ifndef __REQUEST_H__
#define __REQUEST_H__

class Request{
	double time;
	int content_no;

public:
	Request(){;}
	Request(int, double);
	double GetTime(){return time;}
	int GetContentNo(){return content_no;}
	bool operator < (const Request &r)const {
		return time < r.time;
	}
	
};
/*
class compare
{
public:
	compare(){;}
	bool operator () (Request r1,Request r2)
	{
		return r1.getTime() < r2.getTime();
	}
};
*/
#endif

