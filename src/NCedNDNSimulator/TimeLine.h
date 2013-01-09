
#ifndef __TIMELINE_H__
#define __TIMELINE_H__

#include "Task.h"
#include <vector>
#include <list>
using namespace std;



class TimeLine{
	static list<Task*> tasks;
public:
	TimeLine(){;}
	~TimeLine();
	static void Clear();
	static void AddLast(Task*);
	static void Add(Task*);

	static void Execute();
	static int Size();
	

};

#endif
