

#include "ContentCache.h"
#include "CacheElement.h"
#include "Logger.h"

ContentCache::ContentCache(int max_cache_per_content):k(max_cache_per_content){}

ContentCache::~ContentCache()
{
	slices.clear();
}

void ContentCache::Init(int max_cache_per_content)
{
	k = max_cache_per_content;
}
void ContentCache::Add(int slice_no,CacheElement element)
{
	slices[slice_no] = element;
}
void ContentCache::Remove(int slice_no)
{
	Logger::Log(LOGGER_VERY_DETAIL) << "ContentCache::Remove(slice" << slice_no << ")" << endl;
	slices.erase(slice_no);
}

bool ContentCache::Contains(int slice_no)
{
	if(slices.find(slice_no) == slices.end())
		return false;
	return true;
}
/*
std::map<int, CacheElement*> * ContentCache::GetSlices()
{
	return &slices;
}
*/
CacheElement ContentCache::GetElement(int slice_no)
{
	return slices[slice_no];
}
int ContentCache::Size()
{
	Logger::Log(LOGGER_VERY_DETAIL) << "ContentCache::Size()" << endl;
	return slices.size();
}

bool ContentCache::Full()
{
	return slices.size() >= k;
}