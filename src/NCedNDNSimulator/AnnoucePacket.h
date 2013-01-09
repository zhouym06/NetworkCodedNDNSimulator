
#ifndef __ANNOUNCE_PACKET_H__
#define __ANNOUNCE_PACKET_H__

#include "Packet.h"

class AnnoucePacket:public Packet{
	int _server_index;
public:
	AnnoucePacket(){}
	void Init(int server_index, int ttl)
	{
		_server_index = server_index;
		_time_lived = ttl;
	}
	~AnnoucePacket(){}
	int GetServerID(){return _server_index;}
};

#endif
