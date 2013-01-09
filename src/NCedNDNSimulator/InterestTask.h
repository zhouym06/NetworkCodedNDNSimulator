
#ifndef __INTEREST_TASK_H__
#define __INTEREST_TASK_H__

#include "Task.h"
#include <string>

class Router;

class InterestTask:public Task{
	int		_serverNo;
	int		_content_no;
	int		_slice_no;
	Router*	_from;
	Router*	_to;
public:
	InterestTask(int content_no, int slice_no, int server_no, Router* from, Router* to, double time);
	~InterestTask();
	friend class Router;
	friend class Server;
	void Execute();
	void Display();

	
};

#endif
