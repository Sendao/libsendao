#ifndef __SENDAO_RECURSE
#define __SENDAO_RECURSE

typedef class Recursor Recursor;

class Recursor
{
public:
	Recursor();
	~Recursor();

	tlist *stack;
	void *data;

public:
	void Push( void *ptr );
	void PushFront( void *ptr );
	void *Iterate(void);
	bool Ready(void);
};

#endif
