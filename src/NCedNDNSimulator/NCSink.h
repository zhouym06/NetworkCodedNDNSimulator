
#ifndef __NC_SINK_H__
#define __NC_SINK_H__

#include "NCRouter.h"
#include "GaloisApp.h"

#define SINK_BASE -100

class NCSink:public NCRouter{
	int						_content_size;
	int						_content_num;
	int*					_server_of_content;
	NCRouter*				_linkedTo;
	vector<GaloisElemVV>	_already_have;
public:
	NCSink(){}
	~NCSink();
	void Init(int s_id, NCRouter* linkedTo, int content_num, int content_size);
	void Handle();
	NCRouter* GetLinkedTo(){return _linkedTo;}
	void Handle(AnnoucePacket* a_packet, Edge* from_interface, double time);
	void Handle(const NCInterestTask* i_task);
	void Handle(const NCContentTask* c_task);
	void SetServer(const int* server_of_content, int content_num);
};

#endif
