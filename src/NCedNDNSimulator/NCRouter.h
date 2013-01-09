
#ifndef __NC_ROUTER_H__
#define __NC_ROUTER_H__

#include "Router.h"
#include <vector>

#include "FIB.h"
#include "NCPIT.h"
#include "NCLRUCache.h"

class Edge;

class NCInterestTask;
class NCContentTask;
class AnnoucePacket;

class NCRouter: public Router{
protected:
	//int _router_id;

	NCPIT ncpit;
	FIB ncfib;
	NCLRUCache nccache;
	//std::vector<Edge*> interfaces;
public:
	NCRouter();
	~NCRouter();
	void Init(int r_id, int cacheSize, int k, int server_num);
	

	virtual void Handle(const NCInterestTask* i_task);
	virtual void Handle(const NCContentTask* c_task);
	virtual void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	//void AddEdge(Edge* e);
	virtual int GetRouterID(){return _router_id;}

	void DisplayFIB();
	void DisplayCache();
	void Display();
};

#endif
