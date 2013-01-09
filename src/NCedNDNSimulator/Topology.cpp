

#include "Topology.h"
#include "TimeLine.h"
#include "Requests.h"
#include "MyRandom.h"
#include "InterestTask.h"
#include "Sink.h"
#include "Server.h"
#include "Edge.h"

#include "Statistic.h"
#include "Logger.h"

Topology::~Topology()
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
		routers[i].~Router();
	}
	delete[] routers;
	for(int i = 0; i < server_num; i++)
	{
		servers[i].~Server();
	}
	delete[] servers;
	for(int i = 0; i < sink_num; i++)
	{
		sinks[i].~Sink();
	}
	delete[] sinks;
	delete[] server_of_content;
	*/
}


void Topology::SetTimeLine(Requests* reqs, int slice_per_content)
{
	Logger::Log(LOGGER_INFO) << " Topology::SetTimeLine(Requests* reqs, int slice_per_content)" << endl;
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
		//String uri = servers[serverNo].prefix + "-" + String.valueOf(contentNo);
		for(int slice_no = 0; slice_no < slice_per_content; slice_no++)
		{
			//InterestTask* it = new InterestTask(content_no, slice_no, server_no, &sinks[sink_no], sinks[sink_no].GetLinkedTo(), (*(r+i))->GetTime());
			double time = (*(r+i))->GetTime() + 1000 * i;
			InterestTask* it = new InterestTask(content_no, slice_no, server_no, &sinks[sink_no], sinks[sink_no].GetLinkedTo(), time);

			TimeLine::AddLast(it);
			Statistic::CountRequest(content_no);
		}
	}
}


int Topology::GetServerNoOfContent(int ContentNo)
{		
	return server_of_content[ContentNo];
}

void Topology::IssueContentOnServer() {
	Logger::Log(LOGGER_DEBUG) << "Topology::IssueContentOnServer()" << endl;
	server_of_content = new int[content_num];
	for(int i = 0; i < content_num; i++)
	{
		server_of_content[i] = (int) (MyRandom::NextDouble() * server_num);
	}
}

void Topology::Announce()
{
	Logger::Log(LOGGER_DEBUG) << "Topology::Announce()" << endl;
	for(int i = 0; i < server_num; i++)
	{
		Logger::Log(LOGGER_DEBUG) << "Topology:" << "announce(" << "Server" << servers[i].GetRouterID() << ") at Server" << i << std::endl;
		servers[i].Announce(0);
	}
}

void Topology::Display()
{
	Logger::Log(LOGGER_DEBUG) << "Topology::Display()" << endl;
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
