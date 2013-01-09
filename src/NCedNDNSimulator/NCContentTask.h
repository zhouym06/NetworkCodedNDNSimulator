
#ifndef __NC_CONTENT_TASK_H__
#define __NC_CONTENT_TASK_H__

#include "Task.h"
#include "GaloisApp.h"
#include <string>

class NCRouter;

class NCContentTask:public Task{
	int			_content_no;
	GaloisElemV	_factor;
	NCRouter*	_from;
	NCRouter*	_to;
public:
	NCContentTask(){}
	~NCContentTask(){}

	friend class NCRouter;
	friend class NCSink;
	friend class NCPIT;
	friend class NCContentPIT;
	

	void Init(int content_no, GaloisElemV factor, NCRouter* from, NCRouter* to, double time);
	void Execute();
	
};

#endif
