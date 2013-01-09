
#ifndef __CONTENT_TASK_H__
#define __CONTENT_TASK_H__

#include "Task.h"
#include <string>

class Router;

class ContentTask:public Task{
	int	_content_no;
	int	_slice_no;

	Router*	_from;
	Router*	_to;
public:
	ContentTask(){}
	~ContentTask(){}
	friend class Router;
	void Init(int content_no, int slice_no, Router* from, Router* to, double time);
	void Execute();
	int GetSliceNo()const {return _slice_no;};
	int GetContentNo()const {return _content_no;};
	//void Display();
	
};

#endif
