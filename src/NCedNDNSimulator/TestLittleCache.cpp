#include "Tests.h"

#include "RequestsGenerator.h"
#include "Topology.h"
#include "NCTopology.h"
#include "Statistic.h"
#include "TimeLine.h"
#include "Logger.h"

#include <iostream>

void TestLittleCacheLinear()
{
	for(int slice_per_content_i = 0; slice_per_content_i < slice_per_content_l; slice_per_content_i ++)
	{
		int slice_per_content = slice_per_content_s[slice_per_content_i];
		for(int content_num_i = 0; content_num_i < content_num_l; content_num_i ++)
		{
			int content_num = content_num_s[content_num_i];		
			for(int k_i = 0; k_i < k_l; k_i ++)
			{
				if(k_i > 1 && k_s[k_i - 1] > slice_per_content)
					continue;

				int k = k_s[k_i];
				for(double cache_percent = 1; cache_percent <= 10; cache_percent += 1)
				{
					int total_cache_size  = content_num * slice_per_content * cache_percent / 100;
					
						int* cache_sizes = new int[len];
						for(int i = 0; i < len; i++)
						{
							cache_sizes[i] = total_cache_size / len;
						}
						Requests* reqs = RequestsGenerator::GenPoissonRequests(request_num, content_num);
						//Requests* reqs = RequestsGenerator::GenUniformRequests(request_num, content_num);

						char* name = new char[80];


						sprintf(name,"LinearTopoTest-UC-ContentNum%d-ContentSize%d-K%d-TotalCache%d.txt",content_num,slice_per_content,k,total_cache_size);
						if(Logger::Exist(name))
							cout << "skipping" << name << endl;
						else
						{
							cout << "starting" << name << endl;
							Logger::Configure(name, LOGGER_INFO);
							//Logger::Configure(name, LOGGER_DEBUG);
							Topology* line_topo = Topology::GenLineTopo(len, content_num, slice_per_content, k, cache_sizes);
							line_topo->Display();
							Statistic::Init(content_num);
							line_topo->SetTimeLine(reqs, slice_per_content);	
							TimeLine::Execute();
							Statistic::Display();
							delete line_topo;
						}
						sprintf(name,"LinearTopoTest-NC-ContentNum%d-ContentSize%d-K%d-TotalCache%d.txt",content_num,slice_per_content,k,total_cache_size);;
						if(Logger::Exist(name))
							cout << "skipping" << name << endl;
						else
						{
							cout << "starting" << name << endl;
							Logger::Configure(name, LOGGER_INFO);
							//Logger::Configure(name, LOGGER_VERY_DETAIL);
							NCTopology* coded_line_topo = NCTopology::GenLineTopoWithNC(len, content_num, slice_per_content, k, cache_sizes);
							Statistic::Init(content_num);
							coded_line_topo->SetTimeLine(reqs, slice_per_content);
							TimeLine::Execute();
							Statistic::Display();
							delete coded_line_topo;
						}

						delete[] cache_sizes;
						delete[] name;
						
						delete reqs;
					}
			}
		}
	}
}


void TestLittleCacheTree()
{
	for(int slice_per_content_i = 0; slice_per_content_i < slice_per_content_l; slice_per_content_i ++)
	{
		int slice_per_content = slice_per_content_s[slice_per_content_i];
		for(int content_num_i = 0; content_num_i < content_num_l; content_num_i ++)
		{
			int content_num = content_num_s[content_num_i];		
			for(int k_i = 0; k_i < k_l; k_i ++)
			{
				if(k_i > 1 && k_s[k_i - 1] > slice_per_content)
					continue;
				int k = k_s[k_i];
				for(int cache_percent = 1; cache_percent <= 10; cache_percent += 1)
				{
					int total_cache_size  = content_num * slice_per_content * cache_percent / 100;
					int* cache_sizes = new int[level];
					for(int i = 0; i < level; i++)
					{
						cache_sizes[i] = total_cache_size / level;
					}
					Requests* reqs = RequestsGenerator::GenPoissonRequests(request_num, content_num);
					//Requests* reqs = RequestsGenerator::GenUniformRequests(request_num, content_num);

						char* name = new char[80];
						sprintf(name,"TreeTopoTest-UC-ContentNum%d-ContentSize%d-K%d-TotalCache%d.txt",content_num,slice_per_content,k,total_cache_size);
						if(Logger::Exist(name))
							cout << "skipping" << name << endl;
						else
						{
							cout << "starting" << name << endl;
							Logger::Configure(name, LOGGER_INFO);
							//Logger::Configure(name, LOGGER_DEBUG);
							Topology* tree_topo = Topology::GenTreeTopo(level, tree_degree, content_num, slice_per_content, k, cache_sizes);
							tree_topo->Display();
							Statistic::Init(content_num);
							tree_topo->SetTimeLine(reqs, slice_per_content);	
							TimeLine::Execute();
							Statistic::Display();
							delete tree_topo;
						}
						sprintf(name,"TreeTopoTest-NC-ContentNum%d-ContentSize%d-K%d-TotalCache%d.txt",content_num,slice_per_content,k,total_cache_size);;
						if(Logger::Exist(name))
							cout << "skipping" << name << endl;
						else
						{
							cout << "starting" << name << endl;
							Logger::Configure(name, LOGGER_INFO);
							//Logger::Configure(name, LOGGER_VERY_DETAIL);


							NCTopology* coded_tree_topo = NCTopology::GenTreeTopo(level, tree_degree, content_num, slice_per_content, k, cache_sizes);
							Statistic::Init(content_num);
							coded_tree_topo->SetTimeLine(reqs, slice_per_content);
							TimeLine::Execute();
							Statistic::Display();
							delete coded_tree_topo;
						}

						delete[] cache_sizes;
						delete[] name;
						
						delete reqs;
					}
			}
		}
	}

}
