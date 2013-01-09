
#include "NCSink.h"
#include "Logger.h"
#include "AnnoucePacket.h"
#include "NCContentTask.h"
#include "NCInterestTask.h"
#include "TimeLine.h"
#include "Statistic.h"

NCSink::~NCSink()
{
	Logger::Log(LOGGER_DETAIL) << " NCSink::~NCSink()" << endl;
	delete[] _already_have;
}

void NCSink::Init(int s_id, NCRouter* linkedTo, int content_num, int content_size)
{
	_router_id		= s_id;
	_linkedTo		= linkedTo;
	_content_num	= content_num;
	_content_size	= content_size;
	_already_have	= new GaloisElemVV* [content_num];
	for(int i = 0; i < content_num; i++)
	{
		_already_have[i] = new GaloisElemVV();
		_already_have[i]->clear();
	}
}
void NCSink::SetServer(const int* server_of_content, int content_num)
{
	_server_of_content = new int[content_num];
	memcpy(_server_of_content,server_of_content,content_num * sizeof(int));
}

void NCSink::Handle(AnnoucePacket* a_packet, Edge* from_interface, double time)
{
	Logger::Log(LOGGER_DEBUG) << "  NCSink::Handle(AnnoucePacket)" << endl;
	delete a_packet;
	return;
}

void NCSink::Handle(const NCInterestTask* i_task)
{
	Logger::Log(LOGGER_ERROR) << " ERROR!:NCSink::Handle(NCInterestTask)" << endl;
}

void NCSink::Handle(const NCContentTask* c_task)
{
	Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(NCContentTask)" << endl;
	int content_no = c_task->_content_no;
	_already_have[content_no]->push_back(c_task->_factor);
	if(_already_have[content_no]->size() >= _content_size && gaussElimination(*_already_have[content_no]) == 1)
	{
		Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(" << content_no << ") one content fully decoded" << endl;
		_already_have[content_no]->clear();
	}
	else
	{
		Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(" << content_no << ") recieved " << _already_have[content_no]->size() << " slices and need more" << endl;
		//GaloisElemVV evv = *_already_have[content_no];
		GaloisElemVV evv;
		for(GaloisElemVV::iterator it = _already_have[content_no]->begin(); it != _already_have[content_no]->end(); it++)
			evv.push_back(*it);
		double time = c_task->GetTime() + 1;
		NCInterestTask* ncit = new NCInterestTask();
		ncit->Init(content_no, evv,
			_server_of_content[content_no], this, _linkedTo, time);
		TimeLine::Add(ncit);
		Statistic::CountRequest(content_no);
	}
	Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(NCContentTask)fin" << endl;


}