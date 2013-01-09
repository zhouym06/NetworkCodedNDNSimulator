
#include "AnnoucePacket.h"
#include "Server.h"
#include "Edge.h"
#include "Logger.h"
#include "InterestTask.h"
#include "ContentTask.h"
#include "TimeLine.h"
#include "Statistic.h"
#include "Logger.h"

void Server::Init(int r_id)
{
	_router_id = r_id;
}

Server::~Server()
{
	Logger::Log(LOGGER_DETAIL) << " Server::~Server()" << endl;

}
void Server::Announce(double time)
{	
	Logger::Log(LOGGER_DEBUG) << " Server::Announce()" << endl;
	for(std::vector<Edge*>::iterator it = interfaces.begin(); it != interfaces.end(); it++)
	{
		AnnoucePacket* ap = new AnnoucePacket();
		ap->Init(_router_id - SERVER_BASE, 1);
		((*it)->TheOther(this))->Handle(ap, (*it), (*it)->GetDelay());
	}
}

void Server::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_DEBUG) << "  Server::Handle(AnnoucePacket)" << endl;
	delete a_packet;
	return;
}

void Server::Handle(const InterestTask* i_task)
{
	Logger::Log(LOGGER_DEBUG) << " Server::Handle(InterestTask)c" << i_task->_content_no << "s" << i_task->_slice_no << endl;
	ContentTask* ct = new ContentTask();
	double time = i_task->GetTime() + GetServeTime();
	ct->Init(i_task->_content_no, i_task->_slice_no, this, i_task->_from, time);

	Statistic::CountServerLoad(i_task->_content_no);
	TimeLine::Add(ct);
}

void Server::Handle(const ContentTask* c_task)
{
	Logger::Log(LOGGER_ERROR) << " ERROR!:Server::Handle(ContentTask)" << endl;
}

double Server::GetServeTime()
{
	return 0.1;
}
