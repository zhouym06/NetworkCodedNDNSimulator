
#include "FIB.h"
#include "FIBEntry.h"
#include "AnnoucePacket.h"
#include "Logger.h"

#include <string>

FIB::FIB()
{
	inited = NULL;
}
FIB::FIB(int server_num)
{
	_server_num = server_num;
	entries = new FIBEntry[server_num];
	inited = new bool[server_num];
	//inited = new bool(server_num);
	memset(inited, false, sizeof(bool) * server_num);
}
FIB::~FIB()
{
	Logger::Log(LOGGER_DETAIL) << "FIB::~FIB()" << endl;
	//delete[] entries;
	//Logger::Log(LOGGER_DETAIL) << "FIB::~FIB() test" << endl;
	//delete[] inited;
	//Logger::Log(LOGGER_DETAIL) << "FIB::~FIB() fin" << endl;
}
void FIB::Init(int server_num)
{
	Logger::Log(LOGGER_DETAIL) << "FIB::Init(int server_num)" << endl;
	_server_num = server_num;
	entries = new FIBEntry[server_num];
	inited = new bool[server_num];
	memset(inited, false, sizeof(bool) * server_num);
}
/*
Return if the fib entry have been changed
*/
bool FIB::Announce(AnnoucePacket* a_packet, int from_interface, double arrive_time)
{
	Logger::Log(LOGGER_DETAIL) << "FIB::Announce(" << a_packet->GetServerID() <<  ")" << endl;
	int server_id = a_packet->GetServerID();
	if(inited[server_id] == false)
	{
		entries[server_id].Set(a_packet->GetTTL(), arrive_time, server_id, from_interface);
		inited[server_id] = true;
		return true;
	}
	else
	{
		if(entries[server_id]._distance < a_packet->GetTTL())
			return false;
		if(entries[server_id]._distance == a_packet->GetTTL() && entries[server_id]._delay <= arrive_time)
			return false;
		entries[server_id].Set(a_packet->GetTTL(), arrive_time, server_id, from_interface);
		return true;
	}
}

int FIB::GetNextInterface(int server_no)
{
	Logger::Log(LOGGER_VERY_DETAIL) << "FIB::GetNextInterface( " << server_no << ")" << entries[server_no]._next_interface << endl;
	return entries[server_no]._next_interface;
}

double FIB::GetLookupTime()
{
	return (double)_server_num * 0.01;
}


void FIB::Display()
{
	Logger::Log() << "FIB::Display()" << endl;
	for(int i = 0; i < _server_num; i++)
	{
		Logger::Log() << "FIBEntry(" << i << "==" << entries[i]._server_no << ")"
			<< "  next_interface:" << entries[i]._next_interface
			<< "  distance:" << entries[i]._distance
			<< endl;
	}
}