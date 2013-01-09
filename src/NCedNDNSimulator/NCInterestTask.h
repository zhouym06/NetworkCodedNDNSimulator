
#ifndef __NC_INTEREST_TASK_H__
#define __NC_INTEREST_TASK_H__

#include "Task.h"
#include "GaloisApp.h"
#include <string>


class NCRouter;

class NCInterestTask:public Task{
	int				_serverNo;
	int				_content_no;
	GaloisElemVV	_already_have;
	NCRouter*		_from;
	NCRouter*		_to;
public:
	NCInterestTask();
	NCInterestTask(int content_no, GaloisElemVV already_have, int server_no, NCRouter* from, NCRouter* to, double time);
	~NCInterestTask();
	void Init(int content_no, GaloisElemVV already_have, int server_no, NCRouter* from, NCRouter* to, double time);
	friend class NCRouter;
	friend class NCServer;
	void Execute();
	void Display();

	
};

#endif
