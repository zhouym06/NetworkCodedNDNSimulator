

#include "NCTopology.h"
#include "TimeLine.h"
#include "Requests.h"
#include "MyRandom.h"
#include "NCInterestTask.h"
#include "NCSink.h"
#include "NCRouter.h"
#include "NCServer.h"
#include "Edge.h"

#include "Statistic.h"
#include "Logger.h"

NCTopology::~NCTopology()
{
	/*
	for(vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++)
	{
		(*it)->~Edge();
		delete(*it);
	}
	edges.clear();
	for(int i = 0; i < router_num; i++)
	{
		routers[i].~NCRouter();
	}
	delete[] routers;
	for(int i = 0; i < server_num; i++)
	{
		servers[i].~NCServer();
	}
	delete[] servers;
	for(int i = 0; i < sink_num; i++)
	{
		sinks[i].~NCSink();
	}
	delete[] sinks;
	delete[] server_of_content;
	*/
}

void NCTopology::SetTimeLine(Requests* reqs, int slice_per_content)
{
	Logger::Log(LOGGER_INFO) << " NCTopology::SetTimeLine(Requests* reqs, int slice_per_content)" << endl;
	TimeLine::Clear();
	
	int content_no;
	int server_no;
	int sink_no;
	
	Request** r = reqs->GetReqs();
	int req_num = reqs->GetRNum();
	for(int i = 0;i < req_num; i++)
	{
		content_no = (*(r+i))->GetContentNo();
		server_no = GetServerNoOfContent(content_no);
		sink_no = (int) (MyRandom::NextDouble() * sink_num);
		
		GaloisElemVV null_gevv;
		double time = (*(r+i))->GetTime() + 10000000 * i;
		NCInterestTask* ncit = new NCInterestTask();
		ncit->Init(content_no, null_gevv, server_no, &sinks[sink_no], sinks[sink_no].GetLinkedTo(), time);
		TimeLine::AddLast(ncit);
		Statistic::CountRequest(content_no);
	}
	Logger::Log(LOGGER_INFO) << " NCTopology::SetTimeLine(Requests* reqs, int slice_per_content) fin," << TimeLine::Size() << "tasks added" << endl;
}

int NCTopology::GetServerNoOfContent(int ContentNo)
{		
	return server_of_content[ContentNo];
}


void NCTopology::IssueContentOnServer() {
	Logger::Log(LOGGER_DEBUG) << "NCTopology::IssueContentOnServer()" << endl;
	server_of_content = new int[content_num];
	for(int i = 0; i < content_num; i++)
	{
		server_of_content[i] = (int) (MyRandom::NextDouble() * server_num);
	}
}

void NCTopology::Announce()
{
	Logger::Log(LOGGER_DEBUG) << "NCTopology::Announce()" << endl;
	for(int i = 0; i < server_num; i++)
	{
		Logger::Log(LOGGER_DEBUG) << "NCTopology:" << "announce(" << "Server" << servers[i].GetRouterID() << ") at Server" << i << std::endl;
		servers[i].Announce(0);
	}
}

void NCTopology::Display()
{
	Logger::Log(LOGGER_DEBUG) << "NCTopology::Display()" << endl;
	for(int i = 0; i < router_num; i++)
	{
		routers[i].Display();
		routers[i].DisplayFIB();
	}
	for(int i = 0; i < server_num; i++)
	{
		servers[i].Display();
	}
	for(int i = 0; i < sink_num; i++)
	{
		sinks[i].Display();
	}
}

