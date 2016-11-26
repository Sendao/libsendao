#include "sendao.h"
#include "sendao.h"

DMap::DMap( uint32_t gran ) : HTable(gran)
{
}

DMap::~DMap()
{
	Clear( (voidFunction*)free_ivoid );
}

void DMap::CopyFrom( DMap *src, keyFunction *vK, cloneFunction *vC )
{
	if( vK == NULL ) vK = keyof_ivoid;
	if( vC == NULL ) vC = clone_ivoid;
	HTable::CopyFrom( src, vK, vC );
}
void DMap::CopyFrom( tlist *src, keyFunction *vK, cloneFunction *vC )
{
	if( vK == NULL ) vK = keyof_ivoid;
	if( vC == NULL ) vC = clone_ivoid;
	HTable::CopyFrom( src, vK, vC );
}

tlist *DMap::ToList( cloneFunction *vC, bool includeNode )
{
	tlist *nx = new tlist;
	tnode *n;
	ivoid *p, *p2;
	void *px;
	uint32_t i;

	for( i = 0; i < keymax; i++ ) {
		if( tab[i] ) {
			for( n = tab[i]->nodes; n; n = n->next ) {
				p = (ivoid*)n->data;
				if( vC ) {
					px = vC(p->ptr);
					if( !px )
						continue;
					p2 = new_ivoid(p->idc, px);
					nx->PushBack( (void*)p2 );
				} else if( includeNode ) {
					nx->PushBack( clone_ivoid( p ) );
				} else {
					nx->PushBack( p->ptr );
				}
			}
		}
	}

	return nx;
}

ivoid *DMap::Get_( uint32_t idc )
{
	tlist *l = HTable::Search(idc);
	tnode *n;
	ivoid *iv;

	forTLIST( iv, n, l, ivoid* ) {
		if( iv->idc == idc ) {
			return iv;
		}
	}

	return NULL;
}
void *DMap::Get( uint32_t idc )
{
	ivoid *x = Get_(idc);
	return x ? x->ptr : NULL;
}

void DMap::Set( uint32_t idc, void *v )
{
	ivoid *iv = new_ivoid(idc,v);
	HTable::Add(idc,iv);
}

bool DMap::Has( uint32_t idc )
{
	return HTable::Search(idc) != NULL;
}

void DMap::Del( uint32_t idc )
{
	tlist *l = HTable::Search(idc);
	tnode *n, *nn;
	ivoid *iv;

	forTSLIST( iv, n, l, ivoid*, nn ) {
		if( iv->idc == idc ) {
			l->Pull(n);
		}
	}
}



SMap::SMap( uint32_t gran ) : HTable(gran)
{
}

SMap::~SMap()
{
	Clear( (voidFunction*)free_nkvoid );
}

void SMap::CopyFrom( SMap *src, keyFunction *vK, cloneFunction *vC )
{
	if( vK == NULL ) vK = keyof_nkvoid;
	if( vC == NULL ) vC = clone_nkvoid;
	HTable::CopyFrom( src, vK, vC );
}
void SMap::CopyFrom( tlist *src, keyFunction *vK, cloneFunction *vC )
{
	if( vK == NULL ) vK = keyof_nkvoid;
	if( vC == NULL ) vC = clone_nkvoid;
	HTable::CopyFrom( src, vK, vC );
}

tlist *SMap::ToList( cloneFunction *vC, bool includeNode )
{
	tlist *nx = new tlist;
	tnode *n;
	nkvoid *p, *p2;
	void *px;
	uint32_t i;

	for( i = 0; i < keymax; i++ ) {
		if( tab[i] ) {
			for( n = tab[i]->nodes; n; n = n->next ) {
				p = (nkvoid*)n->data;
				if( vC ) {
					px = vC(p->ptr);
					p2 = new_nkvoid(p->name, p->idc, px);
					nx->PushBack( (void*)p2 );
				} else if( includeNode ) {
					nx->PushBack( clone_nkvoid( p ) );
				} else {
					nx->PushBack( p->ptr );
				}
			}
		}
	}

	return nx;
}

nkvoid *SMap::Get_( uint32_t idc )
{
	tlist *l = HTable::Search(idc);
	tnode *n;
	nkvoid *iv;

	forTLIST( iv, n, l, nkvoid* ) {
		if( iv->idc == idc ) {
			return iv;
		}
	}

	return NULL;
}
void *SMap::Get( uint32_t idc )
{
	nkvoid *x = Get_(idc);
	return x ? x->ptr : NULL;
}

nkvoid *SMap::Get_( const char *s )
{
	uint32_t idc = namekey(s);
	tlist *l = HTable::Search(idc);
	tnode *n;
	nkvoid *iv;

	forTLIST( iv, n, l, nkvoid* ) {
		if( iv->idc == idc && str_c_cmp( iv->name, s ) == 0 ) {
			return iv;
		}
	}

	return NULL;
}
void *SMap::Get( const char *s )
{
	nkvoid *x = Get_(s);
	return x ? x->ptr : NULL;
}

void SMap::Set( const char *s, void *v )
{
	uint32_t idc = namekey(s);
	nkvoid *iv = new_nkvoid(s,idc,v);
	HTable::Add(idc,iv);
}

void SMap::Foreach( voidFunction *cb )
{
	uint32_t i;
	tnode *n, *next;
	nkvoid *iv;

	for( i=0; i<keymax; i++ ) {
		if( !tab[i] ) continue;
		forTLIST( iv, n, tab[i], nkvoid* ) {
			cb( iv->ptr );
		}
	}
}

void SMap::Del( uint32_t idc )
{
	tlist *l = HTable::Search(idc);
	tnode *n, *nn;
	nkvoid *iv;

	forTSLIST( iv, n, l, nkvoid*, nn ) {
		if( iv->idc == idc ) {
			l->Pull(n);
		}
	}
}

void SMap::Del( const char *s )
{
	uint32_t idc = namekey(s);
	tlist *l = HTable::Search(idc);
	tnode *n, *nn;
	nkvoid *iv;

	forTSLIST( iv, n, l, nkvoid*, nn ) {
		if( iv->idc == idc && str_c_cmp( iv->name, s ) == 0 ) {
			l->Pull(n);
		}
	}
}

void SMap::Del( nkvoid *ptr )
{
	tlist *l = HTable::Search( ptr->idc );
	tnode *n, *nn;
	nkvoid *iv;

	forTSLIST( iv, n, l, nkvoid*, nn ) {
		if( iv == ptr ) {
			l->Pull(n);
		}
	}
}
