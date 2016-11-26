#include "sendao.h"


SFold::SFold( voidFunction *_free_file_h, int _keymax )
{
	keymax = _keymax;
	root = new SFolder(this, "");
	free_file_h = _free_file_h;
}
SFold::~SFold()
{
	delete root;
}

void *SFold::get( const char *path )
{
	tlist *lPath = split(path, ".");
	char *s = (char*)lPath->FullPop();

	void *ptr = root->get( s, lPath );

	lPath->Clear(free);
	delete lPath;

	return ptr;
}

void SFold::set( const char *path, void *ptr )
{
	tlist *lPath = split(path, ".");
	char *s = (char*)lPath->FullPop();

	root->set( s, lPath, ptr );

	lPath->Clear(free);
	delete lPath;
}

void SFold::del( const char *path, bool isFolder )
{
	tlist *lPath = split(path, ".");
	char *s = (char*)lPath->FullPop();

	root->del( s, lPath, isFolder );
	lPath->Clear(free);

	delete lPath;
}

void SFold::mkfold(const char *path)
{
	tlist *lPath = split(path, ".");
	tnode *n;
	char *s;

	SFolder *prev, *sf;

	if( lPath->count <= 1 ) {
		prev = this->root;
		s = (char*)lPath->FullPop();
		prev->mkfold(s);
	} else {
		prev = this->root;
		forTLIST( s, n, lPath, char* ) {
			sf = prev->getfold(s,NULL);
			if( !sf ) {
				prev->mkfold(s);
				sf = prev->getfold(s,NULL);
			}
			prev = sf;
		}
	}

	lPath->Clear(free);
	delete lPath;
}





SFolder::SFolder(SFold *_base, const char *_name)
{
	base = _base;

	name = strdup(_name);
	folds = new SMap( base->keymax );
	files = new SMap( base->keymax );
}

void free_sfolder( void *p )
{
	SFolder *sf = (SFolder*)p;
	delete sf;
}

SFolder::~SFolder()
{
	folds->Clear( free_sfolder );
	files->Clear( base->free_file_h );
	free(name);
}

void SFolder::mkfold(const char *path)
{
	SFolder *sf = new SFolder(base, path);
	folds->Set( path, (void*)sf );
}

void SFolder::del(const char *thisPath, tlist *nextPath, bool recursive)
{
	SFolder *sf;
	char *s;
	if( nextPath->count > 0 ) {
		sf = (SFolder*)folds->Get( thisPath );
		s = (char*)nextPath->FullPop();
		sf->del(s, nextPath, recursive);
		return;
	}
	if( recursive ) {
		sf = (SFolder*)folds->Get( thisPath );
		if( !sf ) {
			//lprintf("Folder not found %s", thisPath);
			return;
		}
		folds->Del( thisPath );
		delete sf;
	} else {
		void *file = files->Get( thisPath );
		if( !file ) {
			//lprintf("File not found %s", thisPath);
			return;
		}
		files->Del( thisPath );
		this->base->free_file_h(file);
	}
}

void SFolder::set(const char *thisPath, tlist *nextPath, void *ptr)
{
	SFolder *sf;
	char *s;

	if( nextPath->count > 0 ) {
		sf = (SFolder*)folds->Get( thisPath );
		s = (char*)nextPath->FullPop();
		sf->set( s, nextPath, ptr );
		return;
	}
	files->Set( thisPath, ptr );
}

SFolder *SFolder::getfold(const char *thisPath, tlist *nextPath)
{
	SFolder *sf = (SFolder*)folds->Get( thisPath );
	if( nextPath->nodes <= 0 ) return sf;
	char *nextThisPath = (char*)nextPath->FullPop();
	return sf->getfold( nextThisPath, nextPath );
}
