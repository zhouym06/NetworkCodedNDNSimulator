
#ifndef __CONTENT_PIT_H__
#define __CONTENT_PIT_H__

#include <map>
#include <set>
using namespace std; 

class ContentTask;
class Router;

class ContentPIT
{
	int content_no;
	// slice_no	interface
	map<int, set<Router*>> content_table;
public:
	~ContentPIT();
	bool AddPI(int, Router*);
	//set<Router*>GetPI(int slice_no);
	bool Handle(const ContentTask* c_task, Router* from);
	void Display();
	void Clear(int slice_no);
	
};


#endif
