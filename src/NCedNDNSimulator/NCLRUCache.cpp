

#include "NCLRUCache.h"
#include "NCContentElement.h"
#include "Logger.h"

#include <iostream>


NCLRUCache::NCLRUCache()
{
	order.clear();
}

NCLRUCache::~NCLRUCache()
{
	Logger::Log(LOGGER_DETAIL) << "NCLRUCache::~NCLRUCache()" << endl;
	/*
	if(!order.empty())
	{
		for(list<NCContentElement*>::iterator it = order.begin(); it != order.end(); it++)
		{
			delete (*it);
		}
		
	}*/
	//order.clear();
	
}


void NCLRUCache::Init(int size, int max_cache_per_content)
{
	k = max_cache_per_content;
	left = size;
	order.clear();
}

void NCLRUCache::Handle(int content_no, GaloisElemV factor, int element_size)
{
	Logger::Log(LOGGER_ROUTER) << "NCLRUCache::Handle()" << endl;

	if(ContentFull(content_no))
	{
		if(Independent(content_no, factor))
		{
			//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() Independent, recoding" << endl;
			for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
			{
				if(it->_content_no == content_no)
				{
					it->Recode(factor);
				}
			}
		}
		Renew(content_no);
		return;
	}
	if(left >= element_size)					//add new 
	{
		//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() left > 0 add new " << endl;
		AddNew(content_no, factor, element_size);
		//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() add new fin" << endl;
		return;
	}
	if(order.empty())
		return;
	//replace and renew
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() RemoveLast" << endl;
	RemoveLast();
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() RemoveLast fin" << endl;
	
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() add new after removed" << endl;
	AddNew(content_no, factor, element_size);
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() add new fin" << endl;
	Renew(content_no);
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::Handle() Renew fin" << endl;
}

void NCLRUCache::AddNew(int content_no, GaloisElemV factor, int element_size)
{
	//Logger::Log(LOGGER_VERY_DETAIL) << " NCLRUCache::AddNew()" << content_no << endl;
	left -= element_size;
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no)
		{
			it->AddNew(content_no, factor);
			Renew(content_no);
			return;
		}
	}
	NCContentElement elem_p(content_no, factor);
	order.push_front(elem_p);
}

void NCLRUCache::Renew(int content_no)
{
	//Logger::Log(LOGGER_VERY_DETAIL) << " NCLRUCache::Renew()" << content_no << endl;
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no)
		{
			NCContentElement new_nce(it->_content_no, it->_factors);
			order.erase(it);
			//order.remove(*it);
			order.push_front(new_nce);
			return;
		}
	}
	Logger::Log(LOGGER_ERROR) << "NCLRUCache::Renew(" << content_no << ") NULL NCContentElement"  << endl;
}

void NCLRUCache::RemoveLast()
{
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::RemoveLast()" << order.size() << endl;
	//NCContentElement ce_end = order.back();
	if((--order.end())->RemoveLast())
	{
		order.pop_back();
	}
	left++;
	//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::RemoveLast() fin" << endl;
}
/*
void NCLRUCache::RemoveLast(int content_no)
{
	Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::RemoveLast(" << content_no << ")" << endl;
	
	NCContentElement content_end;
	bool not_found = true;
	list<NCContentElement>::iterator it = order.end();
	do
	{
		it--;
		if(it->_content_no == content_no)
		{
			content_end = (*it);
			not_found = false;
		}
	}while(it != order.begin() && not_found);

	if(not_found)
	{
		Logger::Log(LOGGER_ERROR) << "ERROR!: NCLRUCache::RemoveLast() " << "Content Full but content not_found" << endl;
		Display();
		return;
	}
	if(content_end.RemoveLast())
	{
//		order.remove(content_end);
		order.erase(it);
		left++;
		return;

	}
	left++;
	return;
	
	
}
*/

bool NCLRUCache::Contains(int content_no)
{
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no)
			return true;
	}
	return false;
}

bool NCLRUCache::Independent(int content_no, GaloisElemV factor)
{
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no)
		{
			if(independenceMulti(it->_factors,factor))
				return true;
			return false;
		}
	}
	Logger::Log(LOGGER_ERROR) << "NCLRUCache::Independent():content_no not found" << endl;
	return false;
}

bool NCLRUCache::ContainsOther(int content_no, GaloisElemVV already_have_factors)
{
	Logger::Log(LOGGER_DETAIL) << "NCLRUCache::ContainsOther(int content_no, GaloisElemVV already_have_factors)" << endl;

	for(list<NCContentElement>::iterator ce_it = order.begin(); ce_it != order.end(); ce_it++)
	{
		if(ce_it->_content_no == content_no)
		{
			for(GaloisElemVV::iterator fac_it = ce_it->_factors.begin(); fac_it != ce_it->_factors.end(); fac_it++)
			{
				//Logger::Log(LOGGER_VERY_DETAIL) << "NCLRUCache::ContainsOther(" << (fac_it - ce_it->_factors.begin()) << ")" 
				//	<< fac_it->size() << endl;
				if(independenceMulti(already_have_factors,*fac_it))
					return true;
			}
			return false;
		}
	}
	return false;
}

GaloisElemV NCLRUCache::GetOther(int content_no, GaloisElemVV already_have_factors)
{
	Logger::Log(LOGGER_DETAIL) << "NCLRUCache::GetOther(int content_no, GaloisElemVV already_have_factors)" << endl;
	for(list<NCContentElement>::iterator ce = order.begin(); ce != order.end(); ce++)
	{
		if(ce->_content_no == content_no)
		{
			for(GaloisElemVV::iterator it = ce->_factors.begin(); it != ce->_factors.end(); it++)
			{
				if(independenceMulti(already_have_factors,*it))
					return (*it);
			}
			Logger::Log(LOGGER_ERROR) << "NCLRUCache::GetOther(int content_no, GaloisElemVV already_have_factors): No independent Vector" << endl;
			return *already_have_factors.begin();
		}
	}
	Logger::Log(LOGGER_ERROR) << "NCLRUCache::GetOther(int content_no, GaloisElemVV already_have_factors): NULL Content" << endl;
	return *already_have_factors.begin();
}
double NCLRUCache::GetLookupTime()
{
	return ((double)order.size()) * 0.1;
}

bool NCLRUCache::ContentFull(int content_no)
{
	int countent_count = 0;
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		if(it->_content_no == content_no)
		{
			if(it-> GetElementNum() >= k)
				return true;
			return false;
		}
	}
	return false;
}


void NCLRUCache::Display()
{
	Logger::Log(LOGGER_DEBUG) << "NCLRUCache::Display(" << order.size() << ")" << endl;
	for(list<NCContentElement>::iterator it = order.begin(); it != order.end(); it++)
	{
		Logger::Log() << "\tNCContentElement::c" << it->_content_no << "s" << "-" << endl;
	}
}