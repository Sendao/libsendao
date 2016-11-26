#include "sendao.h"

bool cfg_boolean( const char *value, bool default_value )
{
	if( !value || !*value )
		return default_value;
	if( str_cn_cmp(value, "true") == 0 || str_c_cmp(value, "on") == 0 || str_c_cmp(value, "true") == 0 || str_cn_cmp(value, "yes") == 0 || str_c_cmp(value, "1") == 0 ) {
		return true;
	}
	return false;
}



ConfigFile::ConfigFile(void)
{
	configHandlers = new SMap(32);
}
ConfigFile::~ConfigFile(void)
{
	delete configHandlers;
}
void ConfigFile::configure( const char *srch, const char *alias, const char *helpText, configHandler *handle )
{
	configList *sci = (configList*)malloc(sizeof(configList));
	sci->name = strdup(srch);
	sci->alias = strdup(alias);
	sci->help = strdup(helpText);
	sci->test = NULL;
	sci->handle = handle;
	configHandlers->Set( srch, (void*)sci );
	configHandlers->Set( alias, (void*)sci );
}

void ConfigFile::_run( const char *path, SMap *customHandlers )
{
	char *filebuf = readFile(path);
	tlist *lines = split(filebuf, "\n");
	tlist *parsed = NULL;
	tnode *n;
	char *line, *key, *value;
	configHandler *cb;
	configList *sci;

	forTLIST( line, n, lines, char* ) {
		if( *line == '#' ) // comment
			continue;

		parsed = split(line, ":");

		if( parsed->count <= 0 ) continue;

		if( parsed->count == 1 ) {

		} else {
			key = (char*)parsed->FullPop();
			strip_newline(key);
			value = join( parsed, ":" );
			strip_newline(value);
			//lprintf("Config '%s': '%s'", key, value);
			sci = (configList*)customHandlers->Get(key);
			if( sci && sci->handle ) {
				sci->handle(value);
			} else {

			}
			free(value);
			free(key);
		}
	}

	lines->Clear( free );
	delete lines;
}
void ConfigFile::run( const char *path )
{
	ConfigFile::_run(path, configHandlers);
}












ConfigParams::ConfigParams(void)
{
	configHandlers = new SMap(32);
	custom_tests = new tlist;
	paramName = NULL;
	defaultPath = NULL;
}
ConfigParams::~ConfigParams(void)
{
	delete configHandlers;
}
void ConfigParams::configure( const char *srch, const char *alias, const char *helpText, configHandler *handle )
{
	configList *sci = (configList*)malloc(sizeof(configList));
	sci->name = strdup(srch);
	sci->alias = strdup(alias);
	sci->help = strdup(helpText);
	sci->test = NULL;
	sci->handle = handle;
	configHandlers->Set( srch, (void*)sci );
	configHandlers->Set( alias, (void*)sci );
}
void ConfigParams::setConfigFile( const char *_param, const char *_default )
{
	if( _param && *_param )
		this->paramName = strdup(_param);
	if( _default && *_default )
		this->defaultPath = strdup(_default);
}

void ConfigParams::run( int ac, char *av[] )
{
	int i, j;
	bool found;
	configList *cfl;
	bool configLoaded=false;

	if( paramName && *paramName ) {
		for( i=1; av[i]; ++i ) {
			if( str_cmp( av[i], paramName ) == 0 ) {
				// try loading a config file.
				configLoaded=true;
				ConfigFile::_run( av[i+1], configHandlers );
				continue;
			}
		}
	}
	// load default config file.
	if( !configLoaded && ( defaultPath && *defaultPath ) )
		ConfigFile::_run( defaultPath, configHandlers );

	// read params.
	for( i=1; av[i]; ++i ) {
		if( strstr(av[i], "help") != NULL ) {
			printf("Help unavailable...\n");
			exit(0);
		}
		found = false;
		cfl = (configList*)configHandlers->Get(av[i]);
		if( cfl ) {
			if( cfl->handle )
				cfl->handle(av[i+1]);
			++i;
			found=true;
			continue;
		}

		/*
		forTLIST( test, n, custom_tests, sen_test_item* ) {
			found = true;
		} */
		if( found ) continue;
		fprintf(stderr, "Unknown argument '%s'. Use --help to see options.\n", av[i]);
		exit(1);
	}
}
