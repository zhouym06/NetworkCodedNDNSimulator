
#include "ContentTask.h"
#include "PIT.h"
#include "Logger.h"

PIT::PIT()
{
	pending_interests_table.clear();
	inited = true;
}
PIT::~PIT()
{
	Logger::Log(LOGGER_DETAIL) << "PIT::~PIT()" << endl;
	pending_interests_table.clear();
	Logger::Log(LOGGER_DETAIL) << "PIT::~PIT() fin" << endl;
	
}

bool PIT::AddPI(int content_no, int slice_no, Router* pendingSrc)
{
	map<int,ContentPIT>::iterator iter = pending_interests_table.find(content_no);
	if(iter == pending_interests_table.end())
	{
		ContentPIT c_pit;
		pending_interests_table[content_no] = c_pit;
		pending_interests_table[content_no].AddPI(slice_no, pendingSrc);
		return true;
	}
	return pending_interests_table[content_no].AddPI(slice_no, pendingSrc);
}


void PIT::Handle(const ContentTask* c_task, Router* from)
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "PIT::Handle(ContentTask* c_task) fin" << endl;
	if(pending_interests_table.find(c_task->GetContentNo()) == pending_interests_table.end())
	{
		Logger::Log(LOGGER_ERROR) << "PIT::Handle(ContentTask* c_task): content not in pit" << endl;
		return;
	}
	if(pending_interests_table[c_task->GetContentNo()].Handle(c_task, from))
		pending_interests_table.erase(c_task->GetContentNo());
	//Logger::Log(LOGGER_VERY_DETAIL) << "PIT::Handle(ContentTask* c_task) fin" << endl;
	
}
/*
set<Router*> * PIT::GetPI(int content_no, int slice_no)
{
	map<int,ContentPIT*>::iterator iter = pending_interests_table.find(content_no);
	if(iter == pending_interests_table.end())
		return NULL;
	return iter->second->GetPI(slice_no);

}
void PIT::Handle(int content_no, int slice_no)
{
	pending_interests_table[content_no]->Clear(slice_no);
}
*/
double PIT::GetFowardTime()
{
	return ((double)(pending_interests_table.size())) * 0.1;
}


void PIT::Display()
{
	Logger::Log(LOGGER_INFO) << "This PIT have:" << pending_interests_table.size() << "content Entries" << endl;
	for(map<int,ContentPIT>::iterator it = pending_interests_table.begin(); it != pending_interests_table.end(); it++)
	{
		Logger::Log() << "\t PIT's Content No:" << it->first << endl;
		it ->second.Display();
	}
}