
#ifndef __NC_LRU_CACHE_H__
#define __NC_LRU_CACHE_H__


#include "Cache.h"
#include "GaloisApp.h"


#include <map>
#include <list>
using namespace std;

class NCContentElement;

class NCLRUCache: public Cache{
	list<NCContentElement> order;
	//map<int, ContentCache*> content_map;

public:
	NCLRUCache();
	~NCLRUCache();
	void Init(int size, int k);
	bool Contains(int content_no);
	bool ContainsOther(int content_no, GaloisElemVV already_have_factors);
	GaloisElemV GetOther(int content_no, GaloisElemVV already_have_factors);
	void Handle(int content_no, GaloisElemV factor, int element_size = 1);

	void Display();
	void Renew(int content_no);
	double GetLookupTime();
private:
	bool Independent(int content_no, GaloisElemV factor);
	void AddNew(int content_no, GaloisElemV factor, int element_size = 1);
	//NCContentElement* Find(int content_no);
	bool ContentFull(int content_no);
	void RemoveLast();
	void RemoveLast(int content_no);
};

#endif
