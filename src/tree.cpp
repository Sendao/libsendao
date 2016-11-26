#include "sendao.h"

Tree::Tree(sint8_t _keys)
{
	keys = _keys;
	branchfunc = NULL;
	valid = false;
	trunk = NULL;
}

Tree::~Tree()
{
	valid = false;
}

void Tree::Assert(void)
{
	// verify inputs
	if( !branchfunc ) {
		return;
	}
	valid = true;
}

void Tree::Clear(void)
{
	return;
}

TreeBranch *Tree::Seek( void *ptr )
{
	if( !valid ) return NULL;
	return Seek(trunk, ptr);
}

TreeBranch *Tree::Seek( TreeBranch *branch, void *ptr )
{
	if( !branch ) return NULL;
	sint8_t branchkey = branchfunc(branch, ptr);
	TreeBranch *b = (TreeBranch*)branch->forks->Get(branchkey);
	return Seek( b, ptr );
}

TreeBranch *Tree::Seek_( void *ptr )
{
	if( !valid ) return NULL;
	TreeBranch *b, *record=NULL;
	sint8_t branchkey;

	b = trunk;

	do {
		if( !b ) return record;
		record = b;
		branchkey = branchfunc(record, ptr);
		b = (TreeBranch*)record->forks->Get(branchkey);
	} while( true );
}


void Tree::Add( void *ptr )
{
	if( !valid ) return;

	if( trunk ) {
		Add( trunk, ptr );
	} else {
		trunk = new TreeBranch(this);
		trunk->data = ptr;
	}
}

void Tree::Add( TreeBranch *branch, void *ptr )
{
	sint8_t branchkey = branchfunc(branch,ptr);
	TreeBranch *b = (TreeBranch*)branch->forks->Get( branchkey );
	if( !b ) {
		b = new TreeBranch(this);
		b->data = ptr;
		branch->forks->Set( branchkey, (void*)b );
		return;
	}
	Add( b, ptr );
}

void Tree::Add_( void *ptr )
{
	if( !valid ) return;

	TreeBranch *x = new TreeBranch(this);
	x->data = ptr;

	if( !trunk ) {
		trunk = x;
		return;
	}

	TreeBranch *b = trunk;
	TreeBranch *record;
	sint8_t branchkey;

	do {
		record = b;
		branchkey = branchfunc( record, ptr );
		b = (TreeBranch*)record->forks->Get( branchkey );
	} while( b );

	record->forks->Set( branchkey, (void*)x );
}


TreeBranch::TreeBranch( Tree *ofTree )
:
	data( NULL ),
	forks( new DMap(ofTree->keys) )
{
}

TreeBranch::~TreeBranch()
{
	delete forks;
}




HotTree::HotTree(Hot *_hot, sint8_t _keys) :  Tree(_keys), hot(_hot)
{
}

HotTree::~HotTree()
{
}


