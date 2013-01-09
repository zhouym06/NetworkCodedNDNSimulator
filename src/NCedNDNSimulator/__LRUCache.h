
/*
sth wrong that can be seen from log
I think it's caused by deconstructor of class with pointer
Todo:
redesign or copy constructor

or change key from ce* to c_no and s_no
*/

#ifndef __LRU_CACHE_H__
#define __LRU_CACHE_H__


#include "Cache.h"
#include "CacheElement.h"
#include "ContentCache.h"

#include <map>
#include <list>
using namespace std;



class LRUCache: public Cache{
	list<CacheElement> order;
	//content_no
	map<int, ContentCache> content_map;
	//LRUCache(const LRUCache& c);
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
	void AddNew(int content_no, int slice_no, int element_size);
	bool ContentFull(int content_no);
	void RemoveLast();
	void RemoveLast(int content_no);
};

#endif
