#include "sendao.h"

HotPack::HotPack(sint8_t records)
{
	data = new DMap(records);
	hx = new DMap(records);
}

void HotPack::SetHot(sint8_t record, Hot *h)
{
	hx->Set( record, h );
}

void HotPack::Set( sint8_t record, void *ptr )
{
	HotOf *o = new HotOf( (Hot*)hx->Get(record), ptr );
	data->Set( record, (void*)o );
}

HotOf *HotPack::Of( sint8_t record )
{
	return (HotOf*)data->Get(record);
}

void funpackd( int fd, const char *fmt, ... )
{
	va_list args;
	long *len, mylen;
	char *c, **p, **s;

	va_start(args, fmt);
	while( *fmt )
		switch( *fmt++ )
		{
			case 'c':
				c = (char*)va_arg(args, int*);
				read( fd, c, 1 );
				continue;
			case 'l':
				len = (long*)va_arg(args, long*);
				read( fd, len, sizeof(long));
				continue;
			case 's':
				s = (char**)va_arg(args, char**);
				read( fd, &mylen, sizeof(long) );
				*s = (char*)malloc(mylen+1);
				if( mylen != 0 )
					read( fd, *s, mylen );
				s[mylen] = 0;
				continue;
			case 'p': case 'v':
				len = (long*)va_arg(args, long*);
				read( fd, len, sizeof(long) );
				p = (char**)va_arg(args, char**);
				*p = (char*)malloc(*len+1);
				if( *len != 0 )
					read( fd, *p, *len );
				p[*len] = 0;
				continue;
		}
	va_end(args);
}
void fpackd( int fd, const char *fmt, ... )
{
	va_list args;
	long len;
	char c, *p, *s;

	va_start(args, fmt);

	while( *fmt )
	{
		switch( *fmt++ )
		{
			case 'c':
				c = (char)va_arg(args, int);
				write( fd, &c, 1 );
				continue;
			case 'l':
				len = va_arg(args, long);
				write( fd, &len, sizeof(long) );
				continue;
			case 's':
				s = va_arg(args, char*);
				if( !s || !*s ) {
					len=0;
					write( fd, &len, sizeof(long) );
				} else {
					len = (unsigned long)strlen(s);
					write( fd, &len, sizeof(long) );
					write( fd, s, len );
				}
				continue;
			case 'v': case 'p':
				len = va_arg(args, long);
				p = va_arg(args, char*);
				write( fd, &len, sizeof(long) );
				if( len != 0 )
					write( fd, p, len );
				continue;
		}
	}
	va_end(args);
}

