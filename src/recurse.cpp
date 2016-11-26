#include "sendao.h"

Recursor::Recursor()
{
	stack = new tlist;
	data = NULL;
}

Recursor::~Recursor()
{
	delete stack;
}
void Recursor::Push( void *ptr )
{
	stack->PushBack( ptr );
}

void Recursor::PushFront( void *ptr )
{
	stack->Push( ptr );
}

void *Recursor::Iterate( void )
{
	data = stack->FullPop();
	return data;
}

bool Recursor::Ready( void )
{
	return (stack->count>0);
}
