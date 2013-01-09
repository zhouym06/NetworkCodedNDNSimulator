
#include "ContentTask.h"
#include "Router.h"
#include "Logger.h"
#include "Statistic.h"

void ContentTask::Init(int content_no, int slice_no, Router* from, Router* to, double time)
{
	_time		= time;
	_content_no = content_no;
	_slice_no	= slice_no;
	_from		= from;
	_to			= to;
}

void ContentTask::Execute()
{
	Logger::Log(LOGGER_DETAIL) << "ContentTask(c" << _content_no << "s" << _slice_no << ")::Execute from " << _from->GetRouterID() << " to " << _to->GetRouterID() << ")" << std::endl;
	_to->Handle(this);
	Statistic::CountNetworkLoad();
	
}

