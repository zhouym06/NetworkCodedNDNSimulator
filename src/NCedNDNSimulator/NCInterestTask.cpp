
#include "NCInterestTask.h"
#include "NCRouter.h"
#include "Logger.h"

NCInterestTask::NCInterestTask()
{
}
NCInterestTask::NCInterestTask(int content_no, GaloisElemVV already_have, int server_no, NCRouter* from, NCRouter* to, double time)
{
	_serverNo = server_no;
	_content_no = content_no;
	
	_from = from;
	_to = to;
	_time = time;
	_already_have = already_have;
}
NCInterestTask::~NCInterestTask()
{
	Logger::Log(LOGGER_DETAIL) << "NCInterestTask::~NCInterestTask()" << std::endl;
}
void NCInterestTask::Init(int content_no, GaloisElemVV already_have, int server_no, NCRouter* from, NCRouter* to, double time)
{
	_serverNo = server_no;
	_content_no = content_no;
	
	_from = from;
	_to = to;
	_time = time;
	_already_have = already_have;
}

void NCInterestTask::Execute()
{
	Logger::Log(LOGGER_DETAIL) << "NCInterestTask(c" << _content_no << "s" << "-" << "@server" << _serverNo << ")::Execute from " << _from->GetRouterID() << " to " << _to->GetRouterID() << ")" << std::endl;
	_to->Handle(this);
	Logger::Log(LOGGER_DETAIL) << "NCInterestTask(c" << _content_no << "s" << "-" << "@server" << _serverNo << ")::Execute fin" << std::endl;
}


void NCInterestTask::Display()
{
}