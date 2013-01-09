

#include "FIBEntry.h"
#include "Logger.h"

FIBEntry::~FIBEntry()
{
	Logger::Log(LOGGER_DETAIL) << "FIBEntry::~FIBEntry()" << endl;
}

void FIBEntry::Set(int distance, double delay, int server_no, int next_interface)
{
	_distance		= distance;
	_delay			= delay;
	_server_no		= server_no;
	_next_interface = next_interface;
}
