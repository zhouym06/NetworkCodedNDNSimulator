
#ifndef __NC_CONTENT_PIT_H__
#define __NC_CONTENT_PIT_H__

#include "GaloisApp.h"
//#include <map>
#include <list>
using namespace std; 

class NCRouter;
class NCContentTask;

class NCContentPIT
{
	list<pair<NCRouter*,GaloisElemVV>> _already_haves;
public:
	NCContentPIT(){}
	~NCContentPIT();
	void AddPI(GaloisElemVV already_have, NCRouter* source);
	bool Handle(const NCContentTask* c_task, NCRouter* this_router);
	void Display();
	void Clear(int slice_no);
	
};


#endif
