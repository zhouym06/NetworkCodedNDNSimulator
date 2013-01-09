
#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <vector>


#include "FIB.h"
#include "PIT.h"
#include "LRUCache.h"

class Edge;

class InterestTask;
class ContentTask;
class AnnoucePacket;

class Router{
protected:
	int _router_id;


	PIT pit;
	FIB fib;
	LRUCache cache;
	std::vector<Edge*> interfaces;
public:
	Router();
	~Router();

	virtual void Init(int r_id, int cacheSize, int k, int server_num);
	virtual void Handle(const InterestTask* i_task);
	virtual void Handle(const ContentTask* c_task);
	virtual void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	void AddEdge(Edge* e);
	virtual int GetRouterID(){return _router_id;}

	virtual void DisplayFIB();
	virtual void DisplayCache();
	virtual void Display();
};

#endif
