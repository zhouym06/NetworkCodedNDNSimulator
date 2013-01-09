

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
#include "Tree.h"


NCTopology* NCTopology::GenSimpleTreeTopo(int level, int tree_degree, int content_num, int content_size, int k)
{
	int* cache_sizes = new int[level];
	for(int i = 0; i < level; i ++)
	{
		cache_sizes[i] = 10;
	}
	return NCTopology::GenTreeTopo(level, tree_degree, content_num, content_size, k, cache_sizes);
}

NCTopology* NCTopology::GenTreeTopo(int tree_level, int tree_degree, int content_num, int content_size, int k, int* cache_sizes)
{
	Logger::Log(LOGGER_INFO) << "NCTopology::GenLineTopo(tree_level=" << tree_level << ",tree_degree=" << tree_degree << ",content_num=" << content_num << ",content_size=" << content_size << ",k=" << k << ")" << endl;
	NCTopology* topo = new NCTopology();
	
	int router_num = 1;
	int level_num = 1;
	for(int level = 1; level < tree_level; level++)
	{
		level_num *= tree_degree;
		router_num += level_num;
	}
	topo->router_num = router_num;
	topo->routers = new NCRouter[topo->router_num];
	topo->content_num = content_num;
	topo->size_of_content = content_size;
	
	topo->server_num = 1;
	topo->servers = new NCServer[topo->server_num];

	topo->sink_num = level_num;
	topo->sinks = new NCSink[topo->sink_num];

	// NCServer-10
	// NCRouter-0
	//		1	2
	//	3	4	5	6
	//	NCSink  ......  NCSink-100
	topo->edges.clear();
	//routers
	for (int router_id = 0; router_id < topo->router_num; router_id++) {
		topo->routers[router_id].Init(router_id, cache_sizes[Tree::GetTreeLevel(tree_degree, router_id)], k, topo->server_num);
	}
	//NCServer
	for (int server_id = 0; server_id < topo->server_num; server_id++) {
		topo->servers[server_id].Init(SERVER_BASE + server_id, content_size);
	}
	//NCSink
	for (int sink_id = 0; sink_id < topo->sink_num; sink_id++) {
		topo->sinks[sink_id].Init(SINK_BASE + sink_id, &(topo->routers[router_num - 1 - sink_id]), content_num, content_size);
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

	//between routers
	for (int i = 1; i < router_num; i++)
	{
		int parent = Tree::GetParentIndex(tree_degree, tree_level, i);
		for(int j = 0; j < tree_degree; j++)
		{
			Edge* e = new Edge(&topo->routers[i], &topo->routers[parent], i * router_num + j + router_num * 2, MyRandom::NextDouble());
			topo->edges.push_back(e);
			topo->routers[i].AddEdge(e);
			topo->routers[parent].AddEdge(e);
		}
	}
	//servers
	for (int i = 0; i < topo->server_num; i++)
	{
		Edge* e = new Edge(&topo->routers[i], &topo->servers[i], -i, MyRandom::NextDouble());
		topo->routers[i].AddEdge(e);
		topo->servers[i].AddEdge(e);
	}
	//sinks
	for (int i = 0; i < topo->sink_num; i++)
	{
		Edge* e = new Edge(&topo->routers[router_num - i - 1], &topo->sinks[i], -1, MyRandom::NextDouble());
		topo->routers[router_num - i - 1].AddEdge(e);
		topo->sinks[i].AddEdge(e);
	}
	topo->IssueContentOnServer();
	topo->Announce();
	for (int sink_id = 0; sink_id < topo->sink_num; sink_id++) {
		topo->sinks[sink_id].SetServer(topo->server_of_content, content_num);
	}

	return topo; 
}

