
#include "Task.h"
#include "Logger.h"

Task::Task()
{
	;
}
Task::Task(double time)
{
	_time = time;
}
Task::~Task()
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "Task::~Task()" << endl;
	;
}
void Task::Execute()
{
	Logger::Log(LOGGER_ERROR) << "Shouldn't be executed @Task::Execute()" << endl;
}

void Task::Display()
{
	Logger::Log(LOGGER_ERROR) << "Shouldn't be executed @Task::Display()" << endl;
}