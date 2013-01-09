
#ifndef __NC_SERVER_H__
#define __NC_SERVER_H__

#include "NCRouter.h"
#define SERVER_BASE -10

class NCServer:public NCRouter{
	int _content_size;

public:
	NCServer(){}
	~NCServer();
	void Init(int r_id, int content_size);
	void Announce(double time);
	int GetRouterID(){return _router_id - SERVER_BASE;}
	void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	void Handle(const NCInterestTask* i_task);
	void Handle(const NCContentTask* c_task);
	double GetServeTime();
};

#endif
