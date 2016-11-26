#ifndef __SENDAO_HOT
#define __SENDAO_HOT

typedef class Hot Hot;
typedef class HotOf HotOf;

class Hot
{
public:
	Hot(allocFunction *_alloc, cloneFunction *_clone, voidFunction *_free) : alloc(_alloc), clone(_clone), free(_free) {};

	allocFunction *alloc;
	cloneFunction *clone;
	voidFunction *free;

	~Hot();

public:
	HotOf Of(void *ptr);

};

class HotOf
{
public:
	HotOf( Hot *_hot, void *_ptr )	: hot( _hot ), 		ptr( _ptr ), 			allocated(false) {};
	HotOf( Hot *_hot ) 				: hot( _hot ), 		ptr( _hot->alloc() ), 			allocated(true) {};
	HotOf( HotOf *_hotof )			: hot( _hotof->hot ), ptr( _hotof->hot->clone( _hotof->ptr ) ), allocated(true) {};

	Hot *hot;
	void *ptr;
	bool allocated;

	~HotOf() {
		if( allocated )
			hot->free(ptr);
	}
public:
	void *clone() { return hot->clone( ptr ); };
};

#endif
