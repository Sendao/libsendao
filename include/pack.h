#ifndef __SENDAO_PACK
#define __SENDAO_PACK


typedef class HotPack HotPack;

/*
typedef class Pack Pack;


class Pack
{
public:
	Pack(const char *_fmt, ...);
	~Pack();

public:
	void Un(...);
	char *fmt;
	HotOf *Get(int n);
	void Set(int n, void *ptr);

};
*/

class HotPack
{
public:
	HotPack(sint8_t records);
	~HotPack();

public:
	DMap *data;
	DMap *hx;

	void SetHot( sint8_t record, Hot *h );

public:
	void Set( sint8_t record, void *ptr );
	HotOf *Of( sint8_t record );
};

void funpackd( int fd, const char *fmt, ... );
void fpackd( int fd, const char *fmt, ... );


#endif
