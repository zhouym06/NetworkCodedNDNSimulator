

#include "ContentPIT.h"
#include "Logger.h"
#include "Router.h"
#include "ContentTask.h"
#include "TimeLine.h"

ContentPIT::~ContentPIT()
{
	Logger::Log(LOGGER_DETAIL) << "ContentPIT::~ContentPIT()" << endl;
	/**/
	for(map<int, set<Router*>>::iterator set_iter = content_table.begin(); set_iter != content_table.end(); set_iter++)
	{
		set_iter->second.clear();
	}
	content_table.clear();
}
bool ContentPIT::AddPI(int slice_no, Router* pendingSrc)
{
	map<int, set<Router*>>::iterator iter = content_table.find(slice_no);
	if(iter == content_table.end())
	{
		set<Router*> router_v;
		router_v.insert(pendingSrc);
		content_table[slice_no] = router_v;
		return true;
	}
	if(content_table[slice_no].find(pendingSrc) != content_table[slice_no].end())
		return false;
	content_table[slice_no].insert(pendingSrc);
	return true;
}
bool ContentPIT::Handle(const ContentTask* c_task, Router* from)
{
	if(content_table.find(c_task->GetSliceNo()) == content_table.end())
	{
		Logger::Log(LOGGER_ERROR) << "ERROR: ContentPIT::Handle(ContentTask* c_task): sliceNo not found"  << endl;
		return true;
	}
	for(set<Router*>::iterator it = content_table[c_task->GetSliceNo()].begin(); it != content_table[c_task->GetSliceNo()].end(); it++)
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << " ContentPIT::Handle(ContentTask* c_task) foward to router" << (*it)->GetRouterID()  << endl;
		ContentTask* ct = new ContentTask();
		//double time = c_task->GetTime() + content_table.size() * 0.1;
		double time = c_task->GetTime() + 1 * 0.1;
		ct->Init(c_task->GetContentNo(),c_task->GetSliceNo(), from, *it, time);
		TimeLine::Add(ct);
	}
	content_table.erase(c_task->GetSliceNo());
	
	//Logger::Log(LOGGER_VERY_DETAIL) << "ContentPIT::Handle(ContentTask* c_task) fin" << endl;
	if(content_table.size() == 0)
		return true;
	return false;
}
	

/*
set<Router*>* ContentPIT::GetPI(int slice_no)
{
	map<int, set<Router*>*>::iterator iter = content_table.find(slice_no);
	if(iter == content_table.end())
		return NULL;
	return iter->second;
}
*/
void ContentPIT::Clear(int slice_no)
{
	content_table[slice_no].clear();
	content_table.erase(slice_no);
}

void ContentPIT::Display()
{
	Logger::Log() << "\t ContentPIT's Content No:" << content_no << endl;
	for(map<int, set<Router*>>::iterator set_iter = content_table.begin(); set_iter != content_table.end(); set_iter++)
	{
		Logger::Log() << "\t\t Slice No:" << set_iter->first;
		for(set<Router*>::iterator router_iter = set_iter->second.begin(); router_iter != set_iter->second.end(); router_iter++)
		{
			Logger::Log() << "\t\t\tRouter :" << (*router_iter)->GetRouterID();
		}
	}
}