

#include "Edge.h"
#include "Router.h"



Router* Edge::TheOther(Router* r)
{
	if(_r1->GetRouterID() == r->GetRouterID())
		return _r2;
	else if(_r2->GetRouterID() == r->GetRouterID())
		return _r1;
	return NULL;
}