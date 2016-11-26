#ifndef __SENUTIL_H
#define __SENUTIL_H

typedef bool configTester(const char *);
typedef void configHandler(const char *);

typedef struct {
	const char *name;
	const char *alias;
	const char *help;
	configTester *test;
	configHandler *handle;
} configList;

class ConfigFile {
	ConfigFile(void);
	~ConfigFile(void);

	SMap *configHandlers;

public:
	void configure(const char *srch, const char *alias, const char *helpText, configHandler *handle);
	void run(const char *fn);
	static void _run(const char *fn, SMap *customHandlers);
};
class ConfigParams {
	ConfigParams(void);
	~ConfigParams(void);

	SMap *configHandlers;
	tlist *custom_tests;
	char *paramName;
	char *defaultPath;

public:
	void configure(const char *srch, const char *alias, const char *helpText, configHandler *handle);
	void setConfigFile( const char *paramName=NULL, const char *defaultPath=NULL );
	void run(int ac, char *av[]);
};


#endif
