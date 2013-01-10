
#include "NCContentPIT.h"
#include "NCRouter.h"
#include "NCContentTask.h"
#include "TimeLine.h"
#include "GaloisApp.h"
#include "Logger.h"

NCContentPIT::~NCContentPIT()
{
	_already_haves.clear();
}

void NCContentPIT::AddPI(GaloisElemVV already_have, NCRouter* source)
{
	Logger::Log(LOGGER_DETAIL) << "  NCContentPIT::AddPI(GaloisElemVV already_have, NCRouter* source)" << endl;
	_already_haves.push_back(pair<NCRouter*,GaloisElemVV>(source, already_have));
	Logger::Log(LOGGER_DETAIL) << "  NCContentPIT::AddPI(GaloisElemVV already_have, NCRouter* source)fin" << endl;
}


bool NCContentPIT::Handle(const NCContentTask* c_task, NCRouter* this_router)
{
	Logger::Log(LOGGER_DETAIL) << " NCContentPIT::Handle(NCContentTask* ct)" << endl;
	list<pair<NCRouter*,GaloisElemVV>>::iterator it= _already_haves.begin();
	for(;it != _already_haves.end();)
	{
		if(independenceMulti(it->second, c_task->_factor))
		{
			NCContentTask* ct = new NCContentTask();
			ct->Init(c_task->_content_no, c_task->_factor, this_router, it->first, c_task->_time + ((double)_already_haves.size()) * 0.1);
			TimeLine::Add(ct);
			it = _already_haves.erase(it);
			//Logger::Log(LOGGER_VERY_DETAIL) << " NCContentPIT::Handle(NCContentTask* ct):" << "independent." << endl;
		}
		else
		{
			//Logger::Log(LOGGER_VERY_DETAIL) << " NCContentPIT::Handle(NCContentTask* ct):" << "not independent. left" << endl;
			it++;
		}
	}
	if(_already_haves.size() == 0)
	{
		Logger::Log(LOGGER_DETAIL) << " NCContentPIT::Handle(NCContentTask* ct) fin, all consumed" << endl;
		return true;
	}
	Logger::Log(LOGGER_DETAIL) << " NCContentPIT::Handle(NCContentTask* ct) fin, someone left" << endl;
	return false;
}