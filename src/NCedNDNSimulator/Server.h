
#ifndef __SERVER_H__
#define __SERVER_H__

#include "Router.h"
#define SERVER_BASE -10

class Server:public Router{

public:
	Server(){}
	~Server();
	void Init(int r_id);
	void Announce(double time);
	int GetRouterID(){return _router_id - SERVER_BASE;}
	void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	void Handle(const InterestTask* i_task);
	void Handle(const ContentTask* c_task);
	double GetServeTime();
};

#endif
