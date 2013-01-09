
#ifndef __EDGE_H__
#define __EDGE_H__

class Router;

class Edge{
	Router* _r1;
	Router* _r2;
	int _edge_id;
	double _delay;
	
public:
	Edge(Router* r1, Router* r2, int edge_id, double delay):_r1(r1), _r2(r2), _edge_id(edge_id), _delay(delay){}
	~Edge(){}
	Router* TheOther(Router* r);
	double GetDelay(){return _delay;}
	int GetEdgeID(){return _edge_id;}

};

#endif
