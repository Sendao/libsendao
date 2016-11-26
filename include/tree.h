#ifndef __SENDAO_TREE
#define __SENDAO_TREE


typedef class HotTree HotTree;
typedef class Tree Tree;
typedef class TreeBranch TreeBranch;
//typedef class TreeBranch TreeNode;

typedef sint8_t tree_branch_func( TreeBranch *branch, void *ptr );

class Tree
{
public:
	Tree(sint8_t _keys);
	~Tree();

public:
	TreeBranch *trunk;
	sint8_t keys;
	tree_branch_func *branchfunc;

	void Assert(void); // verify inputs
	bool valid;

public:
	TreeBranch *Seek( TreeBranch *branch, void *ptr );
	void Add( TreeBranch *branch, void *ptr );

public:
	TreeBranch *Seek( void *ptr );
	void Add( void *ptr );
	TreeBranch *Seek_( void *ptr ); // does not recurse
	void Add_( void *ptr ); // does not recurse

public:
	void Clear(void);
};


class TreeBranch
{
public:
	TreeBranch(Tree *ofTree);
	~TreeBranch();

public:
	void *data;
	DMap *forks;


public:
	void Add( void *ptr, sint8_t branchkey );
};

class HotTree : Tree
{
public:
	HotTree(Hot *_hot, sint8_t _keys);
	~HotTree();

	Hot *hot;

};

#endif
