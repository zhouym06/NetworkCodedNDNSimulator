
#ifndef __TASK_H__
#define __TASK_H__

//#include <string>
#include <iostream>

class Task{
protected:
	double _time;
public:
	Task();
	Task(double time);
	virtual ~Task();
	virtual void Execute();

	double GetTime()const{	return _time;	}
	virtual void Display();
	
};

#endif
