


#ifndef __NC_CONTENT_ELEMENT_H__
#define __NC_CONTENT_ELEMENT_H__

#include "GaloisApp.h"

class NCContentElement{
	int				_content_no;
	GaloisElemVV	_factors;
public:
	NCContentElement(){}
	NCContentElement(int content_no, GaloisElemV factor);
	NCContentElement(int content_no, GaloisElemVV factors);
	~NCContentElement(){}
	

	friend class NCLRUCache;

	
	void AddNew(int content_no, GaloisElemV factor);
	void Recode(GaloisElemV factor);
	bool RemoveLast();
	int				GetContentNo()		{return _content_no;}
	int				GetElementNum()		{return _factors.size();}
};

#endif
