


#ifndef __CONTENT_CACHE_H__
#define __CONTENT_CACHE_H__

#include <map>
#include <list>
#include "CacheElement.h"


class ContentCache{
	int k;
	std::map<int, CacheElement> slices;
	
public:
	ContentCache(){};
	ContentCache(int max_cache_per_content);
	//ContentCache(const ContentCache& c);
	~ContentCache();
	void Init(int max_cache_per_content);
	
	void Add(int slice_no, CacheElement element);
	void Remove(int slice_no);
	bool Contains(int slice_no);
	//std::map<int, CacheElement*> * GetSlices();
	CacheElement GetElement(int slice_no);
	int Size();
	bool Full();

};

#endif
