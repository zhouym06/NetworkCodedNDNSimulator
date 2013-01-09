

#include "InterestTask.h"
#include "Router.h"
#include "Logger.h"


InterestTask::InterestTask(int content_no, int slice_no, int server_no, Router* from, Router* to, double time):
_serverNo(server_no), _content_no(content_no), _slice_no(slice_no), _from(from), _to(to)
{
	_time = time;
}
InterestTask::~InterestTask()
{
	Logger::Log(LOGGER_DETAIL) << "InterestTask::~InterestTask()" << std::endl;
}

void InterestTask::Execute()
{
	Logger::Log(LOGGER_DETAIL) << "InterestTask(c" << _content_no << "s" << _slice_no << "@server" << _serverNo << ")::Execute from " << _from->GetRouterID() << " to " << _to->GetRouterID() << ")" << std::endl;
	_to->Handle(this);
	
}


void InterestTask::Display()
{
}