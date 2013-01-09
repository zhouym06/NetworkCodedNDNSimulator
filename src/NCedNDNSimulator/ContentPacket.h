
#ifndef __CONTENT_PACKET_H__
#define __CONTENT_PACKET_H__

#include "Packet.h"

__declspec(deprecated) class ContentPacket:public Packet{
public:
	ContentPacket(){}
	~ContentPacket(){}
};

#endif
