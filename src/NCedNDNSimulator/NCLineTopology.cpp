

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


NCTopology* NCTopology::GenLineTopoWithNC(int len, int content_num, int k)
{
	Logger::Log(LOGGER_INFO) << "NCTopology::GenLineTopoWithNC(len=" << len << ",content_num=" << content_num << ",k=" << k << ")" << endl;
	int content_size = 10;
	int* cache_sizes = new int[len];
	for(int i = 0; i < len; i ++)
	{
		cache_sizes[i] = 10;
	}
	return NCTopology::GenLineTopoWithNC(len, content_num, content_size, k, cache_sizes);

}

NCTopology* NCTopology::GenLineTopoWithNC(int len, int content_num, int content_size, int k, int* cacheSizes)
{
	NCTopology* topo = new NCTopology();

	topo->router_num = len;
	topo->routers = new NCRouter[topo->router_num];
	topo->content_num = content_num;
	topo->size_of_content = content_size;
	
	topo->server_num = 1;
	topo->servers = new NCServer[topo->server_num];

	topo->sink_num = 1;
	topo->sinks = new NCSink[topo->sink_num];

	
	//sink-100-0-1- ... - 8-9-server-10
	topo->edges.clear();
	//routers
	for (int router_id = 0; router_id < topo->router_num; router_id++) {
		topo->routers[router_id].Init(router_id, cacheSizes[router_id], k, topo->server_num);
	}
	
	//server
	for (int server_id = 0; server_id < topo->server_num; server_id++) {
		topo->servers[server_id].Init(SERVER_BASE + server_id, content_size);
	}
	//sink
	for (int sink_id = 0; sink_id < topo->sink_num; sink_id++) {
		topo->sinks[sink_id].Init(SINK_BASE + sink_id, &(topo->routers[sink_id]), content_num, content_size);
	}
	//edges
	for (int router_id = 0; router_id < (topo->router_num - 1); router_id++) {
		Edge* e = new Edge(&topo->routers[router_id], &topo->routers[router_id + 1], router_id, MyRandom::NextDouble());
		topo->routers[router_id].AddEdge(e);
		topo->routers[router_id + 1].AddEdge(e);
		topo->edges.push_back(e);
	}
	for (int server_id = 0; server_id < topo->server_num; server_id++) {
		Edge* e = new Edge(&topo->servers[server_id], &topo->routers[topo->router_num - 1 - server_id],server_id-100,MyRandom::NextDouble());
		topo->servers[server_id].AddEdge(e);
		topo->routers[topo->router_num - 1 - server_id].AddEdge(e);
		topo->edges.push_back(e);
	}
	for (int sink_id = 0; sink_id < topo->sink_num; sink_id++) {
		Edge* e = new Edge(&topo->sinks[sink_id], &topo->routers[sink_id],sink_id + SINK_BASE,MyRandom::NextDouble());
		topo->sinks[sink_id].AddEdge(e);
		topo->routers[sink_id].AddEdge(e);
		topo->edges.push_back(e);
	}
	topo->IssueContentOnServer();
	topo->Announce();

	for (int sink_id = 0; sink_id < topo->sink_num; sink_id++) {
		topo->sinks[sink_id].SetServer(topo->server_of_content, content_num);
	}
	return topo; 
}
