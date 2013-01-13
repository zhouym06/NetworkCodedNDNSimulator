
#include "NCRouter.h"
#include "NCInterestTask.h"
#include "NCContentTask.h"
#include "AnnoucePacket.h"
#include "Edge.h"




#include "Logger.h"
#include "TimeLine.h"
#include "Statistic.h"

NCRouter::NCRouter()
{

}

NCRouter::~NCRouter()
{
	Logger::Log(LOGGER_DETAIL) << "NCRouter::~NCRouter(" << _router_id << ")" << endl;
	/*
	delete ncpit;
	Logger::Log(LOGGER_DETAIL) << "NCRouter::~NCRouter() pit test fib" << endl;
	delete ncfib;
	Logger::Log(LOGGER_DETAIL) << "NCRouter::~NCRouter() fib test cache" << endl;
	delete nccache;
	Logger::Log(LOGGER_DETAIL) << "NCRouter::~NCRouter() fin" << endl;
	*/
}

void NCRouter::Init(int r_id, int cacheSize, int k, int server_num)
{
	Logger::Log(LOGGER_DETAIL) << " NCRouter::Init(int r_id, int cacheSize, int k, int server_num)" << endl;
	_router_id = r_id;
	
	ncfib.Init(server_num);
	nccache.Init(cacheSize, k);
	/*
	ncfib = new FIB(server_num);
	ncpit = new NCPIT();
	nccache = new NCLRUCache();
	nccache.Init(cacheSize, k);
	*/
	interfaces.clear();
}



void NCRouter::Handle(const NCInterestTask* i_task)
{
	Logger::Log(LOGGER_DETAIL) 
		<< "NCRouter" << _router_id << "::Handle NCInterestTask(c" << i_task->_content_no << "s" << "-"
		<< "@server" << i_task->_serverNo << ") from router " << i_task->_from->GetRouterID()
		<< " at router " << i_task->_to->GetRouterID() << " == " << _router_id << " at " << i_task->GetTime()
		<< std::endl;
	
	//cache中有该内容且有线性无关内容
	if(nccache.ContainsOther(i_task->_content_no,i_task->_already_have))
	{
		Logger::Log(LOGGER_DEBUG) << " NCRouter" << _router_id << "::Handle(InterestTask) cache begin" << endl;
		//cache->Renew(i_task->_content_no);
		NCContentTask* ct = new NCContentTask();
		ct->Init(i_task->_content_no, nccache.GetOther(i_task->_content_no,i_task->_already_have),this,i_task->_from,
			i_task->GetTime()+nccache.GetLookupTime());
		
		TimeLine::Add(ct);
		Statistic::CountHit(i_task->_content_no);
		Logger::Log(LOGGER_DEBUG) << " NCRouter" << _router_id << "::Handle(InterestTask) cache hit" << endl;
		return;
	}
	//cache中无该内容或仅有线性相关内容
	Statistic::CountMiss(i_task->_content_no);
	//即使pit中已曾经发送该content也要发送
	//Logger::Log(LOGGER_VERY_DETAIL) << " NCRouter::Handle(InterestTask) test1" << endl;
	ncpit.AddPI(i_task->_content_no, i_task->_already_have, i_task->_from);
	//Logger::Log(LOGGER_VERY_DETAIL) << " NCRouter::Handle(InterestTask) test2" << endl;
	int i = ncfib.GetNextInterface(i_task->_serverNo);
	//Logger::Log(LOGGER_VERY_DETAIL) << " NCRouter::Handle(InterestTask) test3" << endl;
	double time = i_task->GetTime() + ncfib.GetLookupTime();
	TimeLine::Add(new NCInterestTask(i_task->_content_no, i_task->_already_have, i_task->_serverNo,
		this, (NCRouter*)interfaces[i]->TheOther(this), time));
	Logger::Log(LOGGER_DEBUG) << " NCRouter" << _router_id << "::Handle(InterestTask) cache miss, pit added, fowarding " << endl;
	return;
}
void NCRouter::Handle(const NCContentTask* c_task)
{
	Logger::Log(LOGGER_DEBUG) << " NCRouter(" << _router_id << ")::Handle(ContentTask c_task):c" 
		<< c_task->_content_no << "s" << "-" << endl;

	nccache.Handle(c_task->_content_no,c_task->_factor);
	Logger::Log(LOGGER_DEBUG) << "cache->Handle fin" << endl;
	ncpit.Handle(c_task, this);
	Logger::Log(LOGGER_DEBUG) << "pit->Handle fin" << endl;
}

void NCRouter::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_ROUTER) << "NCRouter(" << _router_id << ")::Handle AnnoucePacket" << endl;
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
		Logger::Log(LOGGER_ERROR) << "NCRouter::Handle(): from_interface isn't in interfaces" << endl;
		delete a_packet;
		return;
	}
	if(!ncfib.Announce(a_packet, index, time))
	{
		Logger::Log(LOGGER_DETAIL) << "NCRouter(" << _router_id << ")::Handle(AnnoucePacket) FIB already have it." << endl;
		delete a_packet;
		return;
	}
	
	Logger::Log(LOGGER_DETAIL) << "NCRouter(" << _router_id << ")::Handle(AnnoucePacket):  fib renewed, ." << endl;
	for(int j = 0; j < (int)interfaces.size(); j++)
	{
		if(j != index)
		{
			Logger::Log(LOGGER_DETAIL) << "NCRouter(" << _router_id << ")::Handle(AnnoucePacket):  fowarding to others." << j << endl;
			AnnoucePacket* ap = new AnnoucePacket();
			ap->Init(a_packet->GetServerID(), a_packet->GetTTL()+1);
			(interfaces[j]->TheOther(this))->Handle(ap, interfaces[j], time + interfaces[j]->GetDelay());
		}
	}
	delete a_packet;
	return;
}


void NCRouter::DisplayFIB()
{
	Logger::Log(LOGGER_DEBUG) << "NCRouter(" << _router_id << ")::DisplayFIB()" << endl;
	ncfib.Display();
}
void NCRouter::DisplayCache()
{
}
void NCRouter::Display()
{
}