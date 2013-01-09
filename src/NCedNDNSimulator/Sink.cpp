
#include "Sink.h"
#include "Logger.h"
#include "AnnoucePacket.h"

Sink::~Sink()
{
	Logger::Log(LOGGER_DETAIL) << " Sink::~Sink()" << endl;
}

void Sink::Init(int s_id, Router* linkedTo)
{
	_router_id = s_id;
	_linkedTo = linkedTo;
}

void Sink::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_DEBUG) << "  Sink::Handle(AnnoucePacket)" << endl;
	delete a_packet;
	return;
}

void Sink::Handle(const InterestTask* i_task)
{
	Logger::Log(LOGGER_ERROR) << " ERROR!:Sink::Handle(InterestTask)" << endl;
}

void Sink::Handle(const ContentTask* c_task)
{
	Logger::Log(LOGGER_DEBUG) << " Sink::Handle(ContentTask)" << endl;
}