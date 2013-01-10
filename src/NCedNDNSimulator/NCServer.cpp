

#include "AnnoucePacket.h"
#include "Edge.h"
#include "Logger.h"
#include "NCInterestTask.h"
#include "NCContentTask.h"
#include "TimeLine.h"
#include "Statistic.h"

#include "GaloisApp.h"

#include "NCServer.h"




NCServer::~NCServer()
{
	Logger::Log(LOGGER_DETAIL) << " NCServer::~NCServer()" << endl;
}

void NCServer:: Init(int r_id, int content_size)
{
	_router_id = r_id;
	_content_size = content_size;
}


void NCServer::Announce(double time)
{	
	Logger::Log(LOGGER_DEBUG) << " NCServer::Announce()" << endl;
	for(std::vector<Edge*>::iterator it = interfaces.begin(); it != interfaces.end(); it++)
	{
		AnnoucePacket* ap = new AnnoucePacket();
		ap->Init(_router_id - SERVER_BASE, 1);
		((*it)->TheOther(this))->Handle(ap, (*it), (*it)->GetDelay());
	}
}

void NCServer::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_DEBUG) << "  NCServer::Handle(AnnoucePacket)" << endl;
	delete a_packet;
	return;
}

void NCServer::Handle(const NCInterestTask* i_task)
{
	Logger::Log(LOGGER_DEBUG) << " NCServer::Handle(NCInterestTask)c" << i_task->_content_no << "s" << "-" << endl;
	
	
	double time = i_task->GetTime() + GetServeTime();
	NCContentTask* ct = new NCContentTask();
	ct->Init(i_task->_content_no, generateRandomNC(8), this, i_task->_from, time);

	Statistic::CountServerLoad(i_task->_content_no);
	TimeLine::Add(ct);
	/**/
}

void NCServer::Handle(const NCContentTask* c_task)
{
	Logger::Log(LOGGER_ERROR) << " ERROR!:NCServer::Handle(NCContentTask)" << endl;
}

double NCServer::GetServeTime()
{
	return 0.1;
}
