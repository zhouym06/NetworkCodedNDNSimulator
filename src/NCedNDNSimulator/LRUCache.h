
#ifndef __LRU_CACHE_H__
#define __LRU_CACHE_H__


#include "Cache.h"


#include <map>
#include <list>
using namespace std;

class CacheElement;

class LRUCache: public Cache{
	list<CacheElement*> order;
	//map<int, ContentCache*> content_map;

public:
	LRUCache(){}
	~LRUCache();
	void Init(int size, int k);
	bool Contains(int content_no, int slice_no);
	void Handle(int content_no, int slice_no, int element_size = 1);
	void Display();
	void Renew(int content_no, int slice_no);
private:
	bool Contains(int content_no);
	CacheElement* Find(int content_no, int slice_no);
	void AddNew(int content_no, int slice_no, int element_size);
	bool ContentFull(int content_no);
	void RemoveLast();
	void RemoveLast(int content_no);
};

#endif
