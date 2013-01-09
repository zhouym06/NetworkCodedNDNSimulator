
#ifndef __FIB_H__
#define __FIB_H__

class AnnoucePacket;
class FIBEntry;

class FIB{
	int _server_num;
	FIBEntry* entries;
	bool* inited;
public:
	FIB();
	FIB(int server_num);
	~FIB();
	void Init(int server_num);
	int GetNextInterface(int server_no);
	bool Announce(AnnoucePacket* a_packet, int from_interface, double arrive_time);
	double GetLookupTime();
	void Display();
};

#endif
