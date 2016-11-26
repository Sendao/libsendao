#ifndef __SENDAO_FOLDS_H
#define __SENDAO_FOLDS_H


typedef class SFold SFold;
typedef class SFolder SFolder;


class SFold
{
public:
	SFold(voidFunction *_free_file_h, int _keymax=32);
	~SFold();

public:
	int keymax;
	SFolder *root;
	voidFunction *free_file_h; // free file pointers

public: // aliases for this->root->$*
	void set(const char *path, void *ptr); // files only
	void *get(const char *path); // files only
	void mkfold(const char *path); // make empty directory list
	void del(const char *path, bool isFolder=false); // delete recursive folder or single file
	SFolder *getfold(const char *path);
};

class SFolder
{
public:
	SFolder(SFold *_base, const char *_name);
	~SFolder();

public:
	char *name;
	SFold *base;
	SMap *folds;
	SMap *files;

public:
	SFolder *getfold(const char *path, tlist *nextPath=NULL);
	void set(const char *path, tlist *nextPath, void *ptr);
	void mkfold(const char *path);
	void del(const char *path, tlist *nextPath, bool isFolder=false);
	void *get(const char *path, tlist *nextPath); // files only
};

#endif
