
#ifndef __PACKET_H__
#define __PACKET_H__


class Packet{
protected:
	int _content_no;
	int _slice_no;
	int _time_lived;
public:
	Packet(){}
	~Packet(){}
	int GetTTL(){return _time_lived;}
};

#endif
