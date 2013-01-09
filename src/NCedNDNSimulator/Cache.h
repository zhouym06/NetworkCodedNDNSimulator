
#ifndef __CACHE_H__
#define __CACHE_H__


class Cache{
protected:
	int k; //max_cache_per_content
	int left;
public:
	Cache(){}
	~Cache(){}
	virtual void Init(int size, int k);
};

#endif
