
#ifndef __TOPOLOGY_H__
#define __TOPOLOGY_H__

#include <vector>

class Router;
class Server;
class Sink;
class Requests;
class Edge;

class Topology{
	int router_num;
	Router* routers;

	int server_num;
	Server* servers;

	int sink_num;
	Sink* sinks;

	int content_num;
	int* server_of_content;
	
	int size_of_content;
	std::vector<Edge*> edges;

public:
	Topology(){;}
	Topology(int);
	~Topology();

	static Topology* GenLineTopo(int len, int content_num, int content_size, int k);
	static Topology* GenLineTopo(int len, int content_num, int content_size, int k, int* cacheSizes);
	static Topology* GenSimpleTreeTopo(int level, int tree_degree, int content_num, int content_size, int k);
	static Topology* GenTreeTopo(int tree_level, int tree_degree, int content_num, int content_size, int k, int* cache_sizes);


	void SetTimeLine(Requests* reqs, int slice_per_content);
	int GetServerNoOfContent(int ContentNo);
	void IssueContentOnServer();
	void Announce();
	void Display();
};

#endif
