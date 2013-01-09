

#include "LRUCache.h"
#include "CacheElement.h"
#include "ContentCache.h"
#include "Logger.h"

#include <iostream>


LRUCache::~LRUCache()
{
	/*
	for(map<int, ContentCache>::iterator it = content_map.begin(); it != content_map.end(); it++)
	{
		it->second.~ContentCache();
	}
	
	for(list<CacheElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		it->~CacheElement();
	}
	*/
	content_map.clear();
	order.clear();
}


void LRUCache::Init(int size, int max_cache_per_content)
{
	k = max_cache_per_content;
	left = size;
	order.clear();
	content_map.clear();
}
bool LRUCache::Contains(int content_no)
{
	if(content_map.find(content_no) == content_map.end())
		return false;
	return true;
}
bool LRUCache::Contains(int content_no, int slice_no)
{
	if(Contains(content_no))
		return content_map[content_no].Contains(slice_no);
	return false;
}
void LRUCache::Handle(int content_no, int slice_no, int element_size)
{
	Logger::Log(LOGGER_ROUTER) << "LRUCache::Handle" << endl;
	if(Contains(content_no, slice_no))			//renew
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() renew" << endl;
		Renew(content_no, slice_no);
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() renew fin" << endl;
		return;
	}
	if(left >= element_size)					//add new 
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() left > 0 add new " << endl;
		AddNew(content_no, slice_no, element_size);
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new fin" << endl;
		return;
	}
	//replace
	if(ContentFull(content_no))
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast" << content_no << endl;
		RemoveLast(content_no);
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast fin" << endl;
	}
	else 
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast" << endl;
		RemoveLast();
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() RemoveLast fin" << endl;
	}
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new after removed" << endl;
	AddNew(content_no, slice_no, 1);
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::Handle() add new fin" << endl;
}

void LRUCache::AddNew(int content_no, int slice_no, int element_size)
{
	left -= element_size;
	CacheElement elem_p(content_no, slice_no, element_size);
	if(!Contains(content_no))
	{
		content_map[content_no].Init(k);;
	}
	content_map[content_no].Add(slice_no,elem_p);
	order.push_front(elem_p);
}

void LRUCache::Renew(int content_no, int slice_no)
{
	CacheElement p = content_map[content_no].GetElement(slice_no);
	for(list<CacheElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no && it->_slice_no == slice_no)
		{
			order.erase(it);
			order.push_front(p);
			return;
		}
	}
}

void LRUCache::RemoveLast()
{
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast()" << order.size() << endl;
	CacheElement ce_end = order.back();
	left += ce_end.GetElementSize();
	int last_content_no = ce_end.GetContentNo();
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast() last_content_no:" << last_content_no << endl;
	if(!Contains(last_content_no))
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!: LRUCache::RemoveLast() order have " << last_content_no
			<< "while content_map doesn't" << endl;
	}
	else if(content_map[last_content_no].Size() == 1)
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast() the only slice" << endl;
		//content_map[last_content_no].~ContentCache();
		content_map.erase(last_content_no);
	}
	else
	{
		Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast() many slices" << endl;
		content_map[last_content_no].Remove(ce_end.GetSliceNo());
	}
	order.pop_back();
	//ce_end.~CacheElement();
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast() fin" << endl;
}
void LRUCache::RemoveLast(int content_no)
{
	Logger::Log(LOGGER_VERY_DETAIL) << "LRUCache::RemoveLast(" << content_no << ")" << endl;
	CacheElement content_end;
	//std::map<int, CacheElement*> * slices = content_map[content_no]->GetSlices();
	//if(slices == NULL)
	if(!Contains(content_no))
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!: LRUCache::RemoveLast()" << "NULL content_map slices" << endl;
		return;
	}
	bool not_found = true;
	list<CacheElement>::iterator it = order.end();
	do
	{
		it--;
		//if(slices->find((*it)-> GetSliceNo()) != slices->end())
		if(content_map[content_no].Contains(it-> GetSliceNo()))
		{
			content_end = *it;
			not_found = false;
		}
	}while(it != order.begin() && not_found);
	if(not_found)
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!: LRUCache::RemoveLast()" << "memeber of slices Not in Order" << endl;
		return;
	}
	left += content_end.GetElementSize();
	content_map[content_no].Remove(content_end.GetSliceNo());
	
	order.erase(it);
	//content_end.~CacheElement();
}


bool LRUCache::ContentFull(int content_no)
{
	if(content_map.find(content_no) == content_map.end())
		return false;
	return content_map[content_no].Full();
}

void LRUCache::Display()
{
	Logger::Log(LOGGER_DEBUG) << "LRUCache::Display(" << content_map.size() << ")" << endl;
	for(map<int, ContentCache>::iterator it = content_map.begin(); it != content_map.end(); it++)
	{
		Logger::Log() << "\tcontent_no" << it->first << endl;

	}
}