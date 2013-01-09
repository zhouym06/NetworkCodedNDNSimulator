
#include "NCPIT.h"
#include "NCRouter.h"
#include "NCContentTask.h"
#include "Logger.h"

NCPIT::NCPIT()
{
	pending_interests_table.clear();
}
NCPIT::~NCPIT()
{
	Logger::Log(LOGGER_DETAIL) << "NCPIT::~NCPIT()" << endl;
	if(!pending_interests_table.empty())
	{
		for(map<int,NCContentPIT*>::iterator it =  pending_interests_table.begin(); it != pending_interests_table.end(); it++)
		{
			delete it->second;
		}
		pending_interests_table.clear();
	}
	
	Logger::Log(LOGGER_DETAIL) << "NCPIT::~NCPIT() fin" << endl;

}
void NCPIT::AddPI(int content_no, GaloisElemVV already_have, NCRouter* pendingSrc)
{
	Logger::Log(LOGGER_DEBUG) << "NCPIT::AddPI(" << content_no << ")" << endl;
	if(pending_interests_table.find(content_no) == pending_interests_table.end())
	{
		Logger::Log(LOGGER_DEBUG) << "NCPIT::AddPI()" << "a new content" << endl;
		pending_interests_table[content_no] = new NCContentPIT();
		pending_interests_table[content_no]->AddPI(already_have, pendingSrc);
	}
	else
	{
		Logger::Log(LOGGER_DEBUG) << "NCPIT::AddPI()" << "a content we already have" << endl;
		pending_interests_table[content_no]->AddPI(already_have, pendingSrc);
	}
	Logger::Log(LOGGER_DEBUG) << "NCPIT::AddPI(" << content_no << ") fin" << endl;
}

void NCPIT::Handle(const NCContentTask* c_task, NCRouter* this_router)
{
	Logger::Log(LOGGER_DEBUG) << "NCPIT::Handle(NCContentTask " << c_task->_content_no << ")" << endl;
	if(pending_interests_table.find(c_task->_content_no) == pending_interests_table.end())
	{
		Logger::Log(LOGGER_DEBUG) << "NCPIT::Handle(NCContentTask):  pending interest table doesn't have the content" << endl;
		return;
	}
	if(pending_interests_table[c_task->_content_no]->Handle(c_task, this_router))
	{
		pending_interests_table.erase(c_task->_content_no);

	}
	Logger::Log(LOGGER_DEBUG) << " NCPIT::Handle(NCContentTask) fin" << endl;
}