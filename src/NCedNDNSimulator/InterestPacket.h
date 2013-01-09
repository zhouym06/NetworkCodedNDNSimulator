
#ifndef __INTEREST_PACKET_H__
#define __INTEREST_PACKET_H__

#include "Packet.h"

__declspec(deprecated) class InterestPacket:public Packet{
public:
	InterestPacket(){}
	~InterestPacket(){}
};

#endif
