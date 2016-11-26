#ifndef _SENDAO_MAPS
#define _SENDAO_MAPS

/*
#### class DMap
Maps intvoid

#### class TMap
Maps inttype

#### class SMap
Maps namekeyvoid

#### class OMap
Maps namekeytype
*/


typedef class DMap DMap;
typedef class SMap SMap;

class DMap : public HTable { // map ivoid
public:
	DMap(uint32_t granularity);
	virtual ~DMap();

	DMap(DMap *);
	virtual void CopyFrom(DMap *src, keyFunction *vK=NULL, cloneFunction *vC=NULL);
	virtual void CopyFrom(tlist *src, keyFunction *vK=NULL, cloneFunction *vC=NULL);
	tlist *ToList(cloneFunction *cF=NULL, bool includeNode=false);

	void Remove( uint32_t idcode, void *v ) {
		ivoid *x = Get_(idcode);
		HTable::Remove(idcode, (void*)x);
		free_ivoid(x);
	};

	ivoid *Get_(uint32_t idcode);
	void *Get(uint32_t idcode);
	void Set(uint32_t idcode, void *v);
	void Del(uint32_t idcode);
	bool Has( uint32_t idc );
};

class SMap : public HTable { // map nkvoid
	public:
	SMap(uint32_t granularity);
	virtual ~SMap();

	SMap(SMap *);
	virtual void CopyFrom(SMap *src, keyFunction *vK=NULL, cloneFunction *vC=NULL);
	virtual void CopyFrom(tlist *src, keyFunction *vK=NULL, cloneFunction *vC=NULL);
	virtual tlist *ToList(cloneFunction *cF=NULL, bool includeNode=false);
	virtual void Foreach( voidFunction *cb );

	void Remove( uint32_t idcode, void *v ) {
		nkvoid *x = Get_(idcode);
		HTable::Remove(idcode, (void*)x);
		free_nkvoid(x);
	};

	nkvoid *Get_(uint32_t idcode);
	nkvoid *Get_(const char *s);
	void *Get(uint32_t idcode);
	void *Get(const char *s);
	void Set(const char *s, void *v);
	void Del( nkvoid * );
	void Del( uint32_t idcode );
	void Del(const char * );
};

#endif
