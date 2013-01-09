
#ifndef __NC_PIT_H__
#define __NC_PIT_H__

#include "NCContentPIT.h"
#include "GaloisApp.h"
#include <map>
#include <set>

class NCRouter;


class NCPIT
{
	int _content_num;
	map<int,NCContentPIT*> pending_interests_table;
public:
	NCPIT();
	~NCPIT();
	void AddPI(int content_no, GaloisElemVV already_have, NCRouter* pendingSrc);
	void Handle(const NCContentTask* c_task, NCRouter* this_router);//Consume
	//void Display();
	//double GetFowardTime();
};


#endif
