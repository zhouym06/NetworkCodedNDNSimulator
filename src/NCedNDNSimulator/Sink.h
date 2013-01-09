
#ifndef __SINK_H__
#define __SINK_H__

#include "Router.h"

#define SINK_BASE -100

class Sink:public Router{
	Router* _linkedTo;
public:
	Sink(){}
	~Sink();
	void Init(int s_id, Router* linkedTo);
	void Handle();
	Router* GetLinkedTo(){return _linkedTo;}
	void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	void Handle(const InterestTask* i_task);
	void Handle(const ContentTask* c_task);
};

#endif
