
#include "Router.h"

#include "Edge.h"
#include "AnnoucePacket.h"
#include "InterestTask.h"
#include "ContentTask.h"
#include "Logger.h"
#include "TimeLine.h"
#include "Statistic.h"

Router::Router()
{
}


void Router::Init(int r_id, int cacheSize, int k, int server_num)
{
	_router_id = r_id;
	fib.Init(server_num);
	cache.Init(cacheSize, k);
	//interfaces = new vector<Edge>();
}

Router::~Router()
{
	Logger::Log(LOGGER_DETAIL) << "Router::~Router(" << _router_id << ")" << endl;
}

void Router::Handle(const InterestTask* i_task)
{
	Logger::Log(LOGGER_DETAIL) 
		<< "Router::Handle InterestTask(c" << i_task->_content_no << "s" << i_task->_slice_no
		<< "@server" << i_task->_serverNo << ") from router " << i_task->_from->GetRouterID()
		<< " at router " << i_task->_to->GetRouterID() << " == " << _router_id << " at " << i_task->GetTime()
		<< std::endl;
	if(cache.Contains(i_task->_content_no, i_task->_slice_no))
	{
		cache.Renew(i_task->_content_no, i_task->_slice_no);
		ContentTask* ct = new ContentTask();
		//double time = i_task->GetTime() + pit.GetFowardTime();
		double time = i_task->GetTime() + 0.1;
		ct->Init(i_task->_content_no, i_task->_slice_no, this, i_task->_from, time);
		TimeLine::Add(ct);
		Statistic::CountHit(i_task->_content_no);
		Logger::Log(LOGGER_DEBUG) << " Router::Handle(InterestTask) cache hit" << endl;
		return;
	}
	Statistic::CountMiss(i_task->_content_no);
	if(pit.AddPI(i_task->_content_no, i_task->_slice_no, i_task->_from))
	{
		int i = fib.GetNextInterface(i_task->_serverNo);
		double time = i_task->GetTime() + fib.GetLookupTime();
		TimeLine::Add(new InterestTask(i_task->_content_no, i_task->_slice_no, i_task->_serverNo,
			this, interfaces[i]->TheOther(this), time));
		Logger::Log(LOGGER_DEBUG) << " Router::Handle(InterestTask) cache miss, pit added, fowarding " << endl;
		return;
	}
	Logger::Log(LOGGER_DEBUG) << " Router::Handle(InterestTask) same src already sent" << endl;
}
void Router::Handle(const ContentTask* c_task)
{
	Logger::Log(LOGGER_DEBUG) << " Router(" << _router_id << ")::Handle(ContentTask c_task):c" 
		<< c_task->_content_no << "s" << c_task->_slice_no << endl;
	
	cache.Handle(c_task->_content_no,c_task->_slice_no);
	Logger::Log(LOGGER_DEBUG) << "cache.Handle fin" << endl;

	Logger::Log(LOGGER_DEBUG) << " pit.Handle" << endl;
	pit.Handle(c_task, this);
	/*
	set<Router*>* pi = pit.GetPI(c_task->_content_no,c_task->_slice_no);

	Logger::Log(LOGGER_DEBUG) << " pit.GetPI fin" << endl;
	if(pi == NULL)
	{
		Logger::Log(LOGGER_ERROR) << "ERROR: Router(" << _router_id << ")::Handle(ContentTask c_task)" 
			<< "No pending interest for c" << c_task->_content_no << "s" << c_task->_slice_no << endl;
		return;
	}
	for(set<Router*>::iterator it = pi->begin(); it != pi->end(); it++)
	{
		Logger::Log(LOGGER_DEBUG) << " Router(" << _router_id << ")::Handle(ContentTask) foward to router" << (*it)->GetRouterID()  << endl;
		ContentTask* ct = new ContentTask();
		ct->Init(c_task->_content_no,c_task->_slice_no, this, *it, c_task->GetTime() + pi->size() * 0.1);
		TimeLine::Add(ct);
	}
	
	pit.Handle(c_task->_content_no,c_task->_slice_no);
	Logger::Log(LOGGER_DEBUG) << " pit.Handle fin" << endl;
	*/
}

void Router::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_ROUTER) << "Router(" << _router_id << ")::Handle AnnoucePacket" << endl;

	int index = 0;
	bool found = false;
	for(; (index < (int)interfaces.size()) && (!found); index++)
	{
		if(from_interface == interfaces[index])
		{
			found = true;
			break;
		}
	}
	if(!found)
	{
		Logger::Log(LOGGER_ERROR) << "Router::Handle(): from_interface isn't in interfaces" << endl;
		delete a_packet;
		return;
	}
	if(!fib.Announce(a_packet, index, time))
	{
		Logger::Log(LOGGER_DETAIL) << "Router(" << _router_id << ")::Handle(AnnoucePacket) FIB already have it." << endl;
		delete a_packet;
		return;
	}
	
	Logger::Log(LOGGER_DETAIL) << "Router(" << _router_id << ")::Handle(AnnoucePacket):  fib renewed, ." << endl;
	for(int j = 0; j < (int)interfaces.size(); j++)
	{
		if(j != index)
		{
			Logger::Log(LOGGER_DETAIL) << "Router(" << _router_id << ")::Handle(AnnoucePacket):  fowarding to others." << j << endl;
			AnnoucePacket* ap = new AnnoucePacket();
			ap->Init(a_packet->GetServerID(), a_packet->GetTTL()+1);
			(interfaces[j]->TheOther(this))->Handle(ap, interfaces[j], time + interfaces[j]->GetDelay());
		}
	}
	delete a_packet;
	return;
	
	

}

void Router::AddEdge(Edge* e)
{
	interfaces.push_back(e);
}


void Router::DisplayFIB()
{
	Logger::Log(LOGGER_DEBUG) << "Router(" << _router_id << ")::DisplayFIB()" << endl;
	fib.Display();
}
void Router::DisplayCache()
{
}
void Router::Display()
{
}