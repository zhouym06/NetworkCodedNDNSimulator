
#ifndef __NCED_TOPOLOGY_H__
#define __NCED_TOPOLOGY_H__

#include <vector>

class NCRouter;
class NCServer;
class NCSink;
class Requests;
class Edge;

class NCTopology{
	int router_num;
	NCRouter* routers;

	int server_num;
	NCServer* servers;

	int sink_num;
	NCSink* sinks;

	int content_num;
	int* server_of_content;
	
	int size_of_content;
	std::vector<Edge*> edges;

public:
	NCTopology(){;}
	NCTopology(int);
	~NCTopology();

	static NCTopology* GenLineTopoWithNC(int len, int content_num, int k);
	static NCTopology* GenLineTopoWithNC(int len, int content_num, int content_size, int k, int* cacheSizes);
	static NCTopology* GenSimpleTreeTopo(int level, int tree_degree, int content_num, int content_size, int k);
	static NCTopology* GenTreeTopo(int tree_level, int tree_degree, int content_num, int content_size, int k, int* cache_sizes);


	void SetTimeLine(Requests* reqs, int slice_per_content);
	int  GetServerNoOfContent(int ContentNo);
	void IssueContentOnServer();
	void Announce();
	void Display();
};

#endif
