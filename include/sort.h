#ifndef __SENDAO_SORT
#define __SENDAO_SORT


typedef class SortList SortList;


class SortList
{
public:
	SortList();
	~SortList();

public:

public:
	void Add( uint64_t idx, void *data );
	tlist *Slice( uint64_t min, uint64_t max );
	//tlist *
};


#endif
