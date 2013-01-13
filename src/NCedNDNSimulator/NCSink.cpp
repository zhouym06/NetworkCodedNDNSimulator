
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
}

void NCSink::Init(int s_id, NCRouter* linkedTo, int content_num, int content_size)
{
	_router_id		= s_id;
	_linkedTo		= linkedTo;
	_content_num	= content_num;
	_content_size	= content_size;
	_already_have.clear();
	_already_have.reserve(content_num);
	for(int i = 0; i < content_num; i++)
	{
		GaloisElemVV gvv;
		gvv.clear();
		_already_have.push_back(gvv);
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
	int size = _already_have[content_no].size();
	int _rank = 0;
	if(size > 0)
		_rank = rank(_already_have[content_no]);

	if(size > _rank)
		Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(" << content_no << ") recieving content already have" << endl;


	_already_have[content_no].push_back(c_task->_factor);
	size = _already_have[content_no].size();
	int gauss = gaussElimination(_already_have[content_no]);
	
	if(_rank >= _content_size)
	{
		Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(" << content_no << ") one content fully decoded" << endl;
		_already_have[content_no].clear();
	}
	else
	{
		Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(" << content_no << ") recieved " << _already_have[content_no].size() << " slices and need more" << endl;
		GaloisElemVV evv = _already_have[content_no];
		if(size > 2 * _content_size)
		{
			Logger::Log(LOGGER_ERROR) << " NCSink::Handle(const NCInterestTask* i_task)" << c_task->_content_no << ") recieved too much but i_task's already have isn't independent" << _rank << endl;
		}
		double time = c_task->GetTime() + 0.5;
		NCInterestTask* ncit = new NCInterestTask();
		ncit->Init(content_no, evv, _server_of_content[content_no], this, _linkedTo, time);
		TimeLine::Add(ncit);
		Statistic::CountRequest(content_no);
	}
	Logger::Log(LOGGER_DEBUG) << " NCSink::Handle(NCContentTask)fin" << endl;


}