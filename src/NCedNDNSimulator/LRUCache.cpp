

#include "LRUCache.h"
#include "CacheElement.h"
#include "Logger.h"

#include <iostream>


LRUCache::~LRUCache()
{
	if(!order.empty())
	{
		for(list<CacheElement*>::iterator it = order.begin(); it != order.end(); it++)
		{
			delete (*it);
		}
		order.clear();
	}
}


void LRUCache::Init(int size, int max_cache_per_content)
{
	k = max_cache_per_content;
	left = size;
	order.clear();
}

void LRUCache::Handle(int content_no, int slice_no, int element_size)
{
	Logger::Log(LOGGER_ROUTER) << "LRUCache::Handle" << endl;
	if(Contains(content_no, slice_no))			//renew
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() renew" << endl;
		Renew(content_no, slice_no);
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() renew fin" << endl;
		return;
	}
	if(left >= element_size)					//add new 
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() left > 0 add new " << endl;
		AddNew(content_no, slice_no, element_size);
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new fin" << endl;
		return;
	}
	if(order.empty())
		return;
	//replace
	if(ContentFull(content_no))
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast" << content_no << endl;
		RemoveLast(content_no);
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast fin" << endl;
	}
	else 
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast" << endl;
		RemoveLast();
		//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast fin" << endl;
	}
	//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new after removed" << endl;
	AddNew(content_no, slice_no, element_size);
	//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new fin" << endl;
}

void LRUCache::AddNew(int content_no, int slice_no, int element_size)
{
	left -= element_size;
	CacheElement* elem_p = new CacheElement(content_no, slice_no, element_size);
	order.push_front(elem_p);
}

void LRUCache::Renew(int content_no, int slice_no)
{
	CacheElement* p = Find(content_no, slice_no);
	order.remove(p);
	order.push_front(p);
}

void LRUCache::RemoveLast()
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast()" << order.size() << endl;
	CacheElement* ce_end = order.back();
	order.pop_back();
	delete ce_end;
	//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast() fin" << endl;
}
void LRUCache::RemoveLast(int content_no)
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast(" << content_no << ")" << endl;
	CacheElement* content_end = NULL;
	bool not_found = true;
	list<CacheElement*>::iterator it = order.end();
	do
	{
		it--;
		if((*it)->_content_no == content_no)
		{
			content_end = (*it);
			not_found = false;
		}
	}while(it != order.begin() && not_found);

	if(not_found)
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!: LRUCache::RemoveLast() " << "content not_found" << endl;
		Display();
		return;
	}

	order.remove(content_end);
	delete content_end;
}

CacheElement* LRUCache::Find(int content_no, int slice_no)
{
	for(list<CacheElement*>::iterator it = order.begin(); it != order.end(); it++)
	{
		if((*it)->_content_no == content_no && (*it)->_slice_no == slice_no)
			return (*it);
	}
	return NULL;
}


bool LRUCache::Contains(int content_no, int slice_no)
{
	return (Find(content_no, slice_no) != NULL);
}

bool LRUCache::ContentFull(int content_no)
{
	int countent_count = 0;
	for(list<CacheElement*>::iterator it = order.begin(); it != order.end(); it++)
	{
		if((*it)->_content_no == content_no)
			countent_count++;
	}
	if(countent_count >= k)
		return true;
	return false;
}

void LRUCache::Display()
{
	Logger::Log(LOGGER_DEBUG) << "LRUCache::Display(" << order.size() << ")" << endl;
	for(list<CacheElement*>::iterator it = order.begin(); it != order.end(); it++)
	{
		Logger::Log() << "\tCacheElement::c" << (*it)->_content_no << "s" << (*it)->_slice_no << endl;
	}
}