
#ifndef __NULL_STREM_H__
#define __NULL_STREM_H__

#include <iostream>
#include <stdexcept>
#include <fstream>
using namespace std;

class NullStream:public ostream{

public:
	//NullStream(){;}
	//NullStream(const char *filename,int mode = ios::out,int op = filebuf::openprot){;}
	NullStream(): ostream(new filebuf()), ios(0) {;}
	friend  NullStream & operator << (NullStream& ns, char* s){ return ns;}
	friend  NullStream & operator << (NullStream& ns, double s){ return ns;}
	friend  NullStream & operator << (NullStream& ns, int s){ return ns;}
};

#endif
