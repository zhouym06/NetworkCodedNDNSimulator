
#include "NCContentTask.h"
#include "NCRouter.h"
#include "Logger.h"
#include "Statistic.h"

void NCContentTask::Init(int content_no, GaloisElemV factor, NCRouter* from, NCRouter* to, double time)
{
	_time		= time;
	_content_no = content_no;
	_factor		= factor;
	_from		= from;
	_to			= to;
}

void NCContentTask::Execute()
{
	_to->Handle(this);
	Statistic::CountNetworkLoad();
	Logger::Log(LOGGER_DETAIL) << "NCContentTask(c" << _content_no << "s" << "-" << ")::Execute from " << _from->GetRouterID() << " to " << _to->GetRouterID() << ")" << std::endl;
}
