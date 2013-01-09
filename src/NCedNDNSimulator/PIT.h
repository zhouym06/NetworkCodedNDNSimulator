
#ifndef __PIT_H__
#define __PIT_H__

#include "ContentPIT.h"
class Router;


class PIT
{
	map<int,ContentPIT> pending_interests_table;
	bool inited;
public:
	PIT();
	~PIT();
	bool AddPI(int content_no, int slice_no, Router* pendingSrc);
	//set<Router*>* GetPI(int content_no, int slice_no);
	void Display();
	double GetFowardTime();
	void Handle(const ContentTask* c_task, Router* from);
	//void Handle(int contentNo, int sliceNo);
};


#endif
