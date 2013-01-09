

#include "NCFIB.h"
//#include "NCFIBEntry.h"
#include "AnnoucePacket.h"
#include "Logger.h"

#include <string>

NCFIB::NCFIB(int server_num)
{
	_server_num = server_num;
	/*
	entries = new NCFIBEntry*[server_num];
	for(int i = 0; i < _server_num; i++)
	{
		entries[i] = new NCFIBEntry();
	}
	inited = new bool[server_num];
	memset(inited, false, sizeof(inited));
	*/
}
NCFIB::~NCFIB()
{
	/*
	for(int i = 0; i < _server_num; i++)
	{
		entries[i]->~NCFIBEntry();
	}
	delete[] entries;
	delete[] inited;
	*/
}
/*
Return if the fib entry have been changed
*/
bool NCFIB::Announce(AnnoucePacket* a_packet, int from_interface, double arrive_time)
{
	Logger::Log(LOGGER_DETAIL) << "NCFIB::Announce(" << a_packet->GetServerID() <<  ")" << endl;
	/*
	int server_id = a_packet->GetServerID();
	if(inited[server_id] == false)
	{
		entries[server_id]->Set(a_packet->GetTTL(), arrive_time, server_id, from_interface);
		inited[server_id] = true;
		return true;
	}
	else
	{
		if(entries[server_id]->_distance < a_packet->GetTTL())
			return false;
		if(entries[server_id]->_distance == a_packet->GetTTL() && entries[server_id]->_delay <= arrive_time)
			return false;
		entries[server_id]->Set(a_packet->GetTTL(), arrive_time, server_id, from_interface);
		return true;
	}
	*/
	return true;
}

int NCFIB::GetNextInterface(int server_no)
{
	Logger::Log(LOGGER_VERY_DETAIL) << "FIB::GetNextInterface( " << server_no << ")" << endl;
	return 1;
//	Logger::Log(LOGGER_VERY_DETAIL) << "FIB::GetNextInterface( " << server_no << ")" << entries[server_no]->_next_interface << endl;
//	return entries[server_no]->_next_interface;
}

double NCFIB::GetLookupTime()
{
	return (double)_server_num * 0.01;
}


void NCFIB::Display()
{
	Logger::Log() << "FIB::Display()" << endl;
	/*
	for(int i = 0; i < _server_num; i++)
	{
		Logger::Log() << "FIBEntry(" << i << "==" << entries[i]->_server_no << ")"
			<< "  next_interface:" << entries[i]->_next_interface
			<< "  distance:" << entries[i]->_distance
			<< endl;
	}
	*/
}