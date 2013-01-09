
#ifndef __NC_FIB_H__
#define __NC_FIB_H__

class AnnoucePacket;
class NCFIBEntry;

class NCFIB{
	int _server_num;
	NCFIBEntry** entries;
	bool* inited;
public:
	NCFIB(int server_num);
	~NCFIB();
	int GetNextInterface(int server_no);
	bool Announce(AnnoucePacket* a_packet, int from_interface, double arrive_time);
	double GetLookupTime();
	void Display();
};

#endif
