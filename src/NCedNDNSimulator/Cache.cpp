
#include "Cache.h"

#include <iostream>

void Cache::Init(int size, int max_cache_per_content)
{
	std::cout<< "Shouldn't be executed @Cache::Init()" << std::endl;
	k = max_cache_per_content;
	left = size;
}

