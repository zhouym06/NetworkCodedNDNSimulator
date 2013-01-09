


#ifndef __CACHE_ELEMENT_H__
#define __CACHE_ELEMENT_H__


class CacheElement{
	int _content_no;
	int _slice_no;
	int _element_size;
public:
	CacheElement(){}
	CacheElement(int content_no, int slice_no, int element_size = 1);
	~CacheElement(){}
	friend class LRUCache;
	int GetContentNo()		{return _content_no;}
	int GetSliceNo()		{return _slice_no;}
	int GetElementSize()	{return _element_size;}

	bool operator==(const CacheElement &ce) const{ 
         return ((_content_no == ce._content_no) && (_slice_no == ce._slice_no));
     }
};

#endif
