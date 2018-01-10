#include "sendao.h"

void strip_newline( char *str )
{
	char *pFrom, *pTo;

	for( pFrom=str, pTo=str; *pFrom; pFrom++ ) {
		if( *pFrom == '\n' || *pFrom == '\r' )
			continue;
		if( pFrom != pTo )
			*pTo = *pFrom;
		pTo++;
	}
	*pTo = '\0';

	for( pFrom=str, pTo=str; *pFrom; pFrom++ ) {
		if( pTo==str && ( *pFrom == ' ' || *pFrom == '\t' ) )
			continue;
		if( pFrom != pTo )
			*pTo = *pFrom;
		pTo++;
	}
	*pTo = '\0';
	while( pTo>str && ( *(pTo-1) == ' ' || *(pTo-1) == '\t' ) ) {
		pTo--;
		*pTo='\0';
	}
}
void strip_spaces( char *str )
{
	char *pFrom, *pTo;

	for( pFrom=str, pTo=str; *pFrom; pFrom++ ) {
		if( *pFrom == '\n' || *pFrom == '\r' || *pFrom == ' ' || *pFrom == '\t' )
			continue;
		if( pFrom != pTo )
			*pTo = *pFrom;
		pTo++;
	}
	*pTo = '\0';
}

bool is_number(const char *str)
{
    const char *pStr;

    if( !(pStr=str) ) return FALSE;
	if( !*str ) return FALSE;
    if( *str == '-' )
        pStr++;

    while( *pStr )
        if( !isdigit(*pStr++) )
            return FALSE;
    return TRUE;
}
bool is_numeric(const char *c)
{
	return is_number(c);
}

bool strprefix( const char *longstr, const char *shortstr )
{
	const char *lp, *sp;

	for( lp = longstr, sp = shortstr; *sp; sp++, lp++ ) {
		if( *lp != *sp )
			return false;
	}
	return true;
}

void strexpand( char **buf, const char *add )
{
	char *tptr;

	if( !buf )
		return;

	if( !*buf ) {
		tptr = (char*)malloc( strlen(add) + 1 );
		strcpy(tptr, add);
	} else if( !**buf ) {
		tptr = (char*)malloc( strlen(add) + 1 );
		strcpy(tptr, add);
		free(*buf);
	} else {
		tptr = (char*)malloc( strlen(*buf) + strlen(add) + 1 );
		strcpy(tptr, *buf);
		strcat(tptr, add);
		free(*buf);
	}

	*buf = tptr;
}

void Arg(const char *args, int n, char *argn)
{
	const char *pArgs;
	char *pArgn;
	int i;
	bool bRemainder=false;

	if( n < 0 ) {
		bRemainder = true;
		n = (0 - n) + 1;
	}

	// Eliminate leading whitespace
	for( pArgs = args; isspace(*pArgs); pArgs++ );

	// Jump to correct word
	for( i=1; i<n && *pArgs; pArgs++  ) {
		if( isspace(*pArgs) )
			i++;
	}

	// Do remainders' write to argn
	if( bRemainder ) {
		if( !*pArgs )
			*argn = '\0';
		else
			strcpy(argn, pArgs);
		return;
	}

	// Do standard write to argn
	for( pArgn=argn; *pArgs && !isspace(*pArgs); pArgs++, pArgn++ ) {
		*pArgn = *pArgs;
	}
	*pArgn = '\0';

	return;
}


void strcpysafe( char *dst, char *src )
{
	char *pB=dst, *pS=src;
	while( *pS ) {
		*pB = *pS;
		++pS;
		++pB;
	}
	*pB = '\0';
}
char *str_dup( const char *p )
{
	char *px = (char*)malloc( strlen(p)+1 );
	if( *p )
		strcpy(px,p);
	else
		*px = '\0';
	return px;
}


char *str_n_dup(const char *str, int len)
{
	char *x=strncpy((char*)calloc(len+1, 1), str, len);
	x[len]=0;
	return x;
}


int str_c_cmp( const char *a, const char *b )
{
	const char *ax,*bx;
	char c,d;
	for( ax=a,bx=b; *ax || *bx; ax++, bx++ )
	{
		c = LOWER(*ax);
		d = LOWER(*bx);
		if( c != d ) return -1;
	}
	return 0;
}
int str_cn_cmp( const char *a, const char *b )
{
	const char *ax,*bx;
	char c,d;
	for( ax=a,bx=b; *ax && *bx; ax++, bx++ )
	{
		c = LOWER(*ax);
		d = LOWER(*bx);
		if( c != d ) return -1;
	}
	return 0;
}

int str_cmp( const char *a, const char *b )
{
	const char *ax,*bx;

	for( ax=a,bx=b; *ax && *bx; ax++, bx++ )
	{
		if( *ax != *bx ) return -1;
	}
	return 0;
}

const char *str_r_str(const char *src, const char *search)
{
	const char *index;
	const char *srcA, *srcB;

	for( index=src+strlen(src); index>=src; index-- ) {
		if( *index == *search ) {
			srcA=index;
			srcB=search;
			while( *srcA == *srcB ) {
				srcA++; srcB++;
				if( !*srcB ) return index;
			}
		}
	}
	return NULL;
}
int str_lev(const char *A, const char *B)
{
	const char *a, *b, *pA, *pB;
	int dist=0, sma, smb;
	bool found;

	for( a = A, b = B; *a && *b; a++, b++ ) {
		if( *a == *b ) continue;
		found=false;
		for( pA=a,sma=0; *pA; pA++,sma++ ) {
			if( *pA == *b ) {
				found=true;
				break;
			}
		}
		for( pB=b,smb=0; *pB; pB++,smb++ ) {
			if( *a == *pB ) {
				found=true;
				break;
			}
		}
		if( !found ) {
			dist += 1;
			continue;
		}
		if( sma < smb ) {
			dist += sma;
			a = pA;
		} else {
			dist += smb;
			b = pB;
		}

	}

	return dist;
}
const char *str_str(const char *src, const char *search)
{
	const char *index;
	const char *srcA, *srcB;

	for( index=src; *index; index++ ) {
		if( *index == *search ) {
			srcA=index;
			srcB=search;
			while( *srcA == *srcB ) {
				srcA++; srcB++;
				if( !*srcB ) return index;
			}
		}
	}
	return NULL;
}
char *strtoupper( const char *src )
{
	char *buf = (char*)malloc(strlen(src)+1);
	const char *index;
	char *ptr;

	for( index=src,ptr=buf; *index; ++index ) {
		*ptr = UPPER(*index);
		ptr++;
	}
	*ptr='\0';
	return buf;
}
char *strtolower( const char *src )
{
	char *buf = (char*)malloc(strlen(src)+1);
	const char *index;
	char *ptr;

	for( index=src,ptr=buf; *index; ++index ) {
		*ptr = LOWER(*index);
		ptr++;
	}
	*ptr='\0';
	return buf;
}
const char *str_case_str(const char *src, const char *search)
{
	const char *index;
	const char *srcA, *srcB;

	for( index=src; *index; index++ ) {
		if( LOWER(*index) == LOWER(*search) ) {
			srcA=index;
			srcB=search;
			while( *srcA == *srcB ) {
				srcA++; srcB++;
				if( !*srcB ) return index;
			}
		}
	}
	return NULL;
}
const char *str_exp(const char *src, const char *search)
{
	const char *index;
	const char *srcA, *srcB;

	if( search[strlen(search)-1] == '@' ) { // tail end
		srcA=src+strlen(src)-strlen(search);
		srcB=search;
		while( LOWER(*srcA) == LOWER(*srcB) ) {
			srcA++; srcB++;
			if( *srcB ) return src+strlen(src)-strlen(search);
		}
		return NULL;
	}

	for( index=src; *index; index++ ) {
		if( *index == *search ) {
			srcA=index;
			srcB=search;
			while( *srcA == *srcB ) {
				srcA++; srcB++;
				if( !*srcB ) return index;
			}
		}
	}
	return NULL;
}

stringbuf::stringbuf(uint32_t chunk)
{
	len=0;
	alloc_chunk = chunk;
	alloced=0;
	maxlen=0;
	p = NULL;
}
stringbuf::stringbuf(const char *src, uint32_t chunk)
{
	len=strlen(src);
	maxlen = 0;
	alloc_chunk = chunk;
	alloced = 0;
	while(alloced<=len+1)
		alloced += alloc_chunk;
	if( alloced > 0 )
		p = (char*)malloc(alloced);
	else
		p = NULL;
	if( len > 0 )
		strcpy(p,src);
	else if( alloced > 0 )
		*p = '\0';
}

stringbuf::~stringbuf()
{
	if(p!=NULL)
		free(p);
}

void stringbuf::reset(void)
{
	if(p&&len>0)
		*p='\0';
	if(p){
		free(p);
		p=NULL;
	}
	len=0;
}

void stringbuf::insertend(const char *src)
{
	uint32_t newlen = len+strlen(src)+1;
	if( newlen >= alloced ) {
		::printf("insertend had to expand!\n");
		expand( newlen - alloced );
	}
	if( len == 0 )
		strcpy(p,src);
	else
		strcat(p,src);
	len = newlen-1;
}
void stringbuf::append(const char *src)
{
	uint32_t newlen = len+strlen(src)+1;
	if( newlen >= alloced ) expand( newlen - alloced );
	if( len == 0 )
		strcpy(p,src);
	else
		strcat(p,src);
	len=newlen-1;
}
void stringbuf::append(char c)
{
	uint32_t newlen = 1;
	if( len <= 0 ) newlen++;
	expand(newlen);
	p[newlen-1] = c;
	p[newlen] = '\0';
	len++;
}
// void stringbuf::expandto( int target_len )
void stringbuf::expand(int target_len)
{
	if( target_len != 0 ) target_len -= alloced;
	//::printf("expand(%d)\n", target_len);
	while( target_len >= 0 ) {
		alloced += alloc_chunk;
		target_len -= alloc_chunk;
		//::printf("%d %d\n", alloced, target_len);
		if( maxlen!=0 && alloced > maxlen ) {
			alloced = maxlen;
			::printf("Tried to expand buffer over maxlen %d\n", maxlen);
			abort();
			break;
		}
	}
	//::printf("alloced %d target %d\n", alloced, target_len);
	if( alloced == 0 ) {
		p=NULL;
		return;
	}
	char *tmp = (char*)malloc(alloced);
	if( !tmp ) {
		::printf("Tried to allocate %d bytes failed\n", alloced);
		p=NULL;
		abort();
	}
	if(p){
		strcpy(tmp,p);
		free(p);
		p=tmp;
	} else {
		p=tmp;
		*p = '\0';
	}
}
void stringbuf::printf(const char *src,...)
{
    char buf[204800];
    va_list args;

    va_start(args, src);
    ::vsprintf(buf, src, args);
    va_end(args);

	append(buf);
}
int stringbuf::vsprintf(const char *src, va_list args)
{
    char buf[204800];
    int i;

    i=::vsprintf(buf, src, args);

    if( i > 204800 ) {
    	::printf("Buffer overflow.\n");
    	exit(-1);
    }

    if( i > 0 )
    	append(buf);

	return i;
}
void stringbuf::clear(void)
{
	reset();
}
void stringbuf::replace(const char *srch, const char *repl)
{
	char *tgt;
	char *tmp;
	int srchlen = strlen(srch);
	int repllen = strlen(repl);
	int chglen = repllen-srchlen;
	int prelen;

	while( (tgt = strstr(p, srch)) != NULL ) {
		tmp = (char*)malloc(strlen(p) + chglen + 1 );
		prelen = tgt-p;
		strncpy( tmp, p, prelen );
		strncpy( tmp+prelen, repl, repllen );
		strcpy( tmp+prelen+repllen, tgt+srchlen );

		setcontents( tmp );
		free(tmp);
	}
}

void stringbuf::setcontents( const char *newbuffer )
{
	len = strlen(newbuffer);
	expand((len+1)-alloced);
	strcpy(p, newbuffer);
}

linebuf::linebuf(const char *src)
{
	lines=used=0;
	buffer=NULL;
	if( !src ) append("");
	else append(src);
}

void linebuf::setline( int lno, const char *str )
{
	while( lno >= lines ) expand();
	if( buffer[lno] ) free(buffer[lno]);
	buffer[lno] = strdup(str);
	if( lno >= used ) used = lno;
}

void linebuf::append( const char *str )
{
	tlist *lStr = split(str, "\n");

	while( used + lStr->count > lines ) {
		expand();
	}

	char *onestr;
	tnode *n;

	forTLIST( onestr, n, lStr, char* ) {
		addline(onestr);
	}
	lStr->Clear( free );
	delete lStr;
}

void linebuf::addline( const char *str )
{
	if( used + 4 > lines ) expand();

	buffer[used] = strdup(str);
	used++;
}

void linebuf::expand( void )
{
	char **tmp = buffer;
	lines += 128;
	buffer = (char**)malloc( sizeof(char*)*lines );
	if( tmp ) {
		memcpy( buffer, tmp, sizeof(char*)*used );
	} else used=0;
	memset( &buffer[used], 0, sizeof(char*)*(lines-used) );
	free(tmp);
}




bitbuf::bitbuf(uint32_t chunk)
{
	len=0;
	alloc_chunk = chunk;
	alloced=0;
	while(alloced<=len)
		alloced += alloc_chunk;
	p = (char*)calloc(alloced, 1);
}

bitbuf::~bitbuf()
{
	free(p);
}
void bitbuf::append(char *src, int nlen)
{
	uint32_t newlen = len+nlen;
	if( alloced <= newlen ) {
		char *tmp;
		while(alloced<=newlen)
			alloced += alloc_chunk;
		tmp = (char*)calloc(alloced, 1);
		memcpy(tmp,p,len);
		free(p);
		p=tmp;
	}
	memcpy(p+len,src,nlen);
	len=newlen;
	p[len]=0;
}
void bitbuf::clear(void)
{
	len=0;
}


char *join( tlist *x, const char *sep )
{
	tnode *n;
	stringbuf *tgt = new stringbuf();
	char *sptr;
	bool prev=false;

	forTLIST( sptr, n, x, char* ) {
		if( prev ) {
			tgt->append(sep);
		} else {
			prev=true;
		}
		tgt->append(sptr);
	}

	sptr = strdup(tgt->p);

	delete tgt;
	return sptr;
}

tlist *split( const char *str, const char *sep )
{
	tlist *seps = new tlist();
	void *septr = (void*)str_dup(sep);
	seps->Push( septr );
	tlist *tgt = split(str,seps);
	seps->Clear( free );
	delete seps;
	return tgt;
}

tlist *split( const char *str, tlist *seps )
{
	tlist *tgt = new tlist();
	const char *ptr, *lastPtr;
	tnode *n;
	const char *sep;
	char wordBuf[1024];
	int len,ilen;

	for( lastPtr = ptr = str; ptr && *ptr; ptr++ ) {
		ilen=strlen(ptr);
		forTLIST( sep, n, seps, const char* ) {
			len = strlen(sep);
			if( ilen>=len && strncmp(sep,ptr,len) == 0 ) {
				if( ptr != lastPtr ) {
					strncpy(wordBuf,lastPtr,ptr-lastPtr);
				}
				wordBuf[ptr-lastPtr]=0;
				tgt->PushBack( (void*)str_dup(wordBuf) );
				ptr += len-1;
				lastPtr = ptr+1;
				break;
			}
		}
		if( !*ptr ) break;
	}
	if( ptr > lastPtr ) {
		strncpy(wordBuf,lastPtr,ptr-lastPtr);
		wordBuf[ptr-lastPtr]=0;
		tgt->PushBack( (void*)str_dup(wordBuf) );
	}
	return tgt;
}

