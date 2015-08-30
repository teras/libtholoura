#include "tholoura.h"
#include "plugins.h"
#include "defaults.h"

#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>


void thShakeText ( thLib * lib, thText * ttext, int type ) {
	thPlugin * plug;
	int which;

	if ( ttext == NULL || ttext == NULL ) return;
	/* check if no plugins are found */
	if ( lib->plugsize < 1 ) {
		DPRINTL("There are no plugins available. We will just render the image.");
		return;
	}

	which = rand() % lib->plugsize;
	plug = lib->plugins;
	
	while ( which > 0 ) {
		plug = plug->next;
		which--;
	}
	DPRINTS("Plugin used: ");
	DPRINTL(plug->name);

	plug->shakefunc(ttext, 1);
}


/* Cleanly destroy the resources of a plugin */
void thDestroyPlugin(thPlugin * plugin) {
	if ( plugin != NULL ) {
		if ( plugin->filename != NULL ) free(plugin->filename);
		if ( plugin->name != NULL ) free(plugin->name);
		if ( plugin->handler != NULL ) dlclose(plugin->handler);
		free(plugin);
	}
}


void (*getshakefunc( thPlugin * plug))(thText *, float) {
	void (*shake_func)(thText *, float);
	
	char * error;
	
	dlerror();
	shake_func = (void (*)(thText *, float)) dlsym( plug->handler, "shakeIt" ) ;
	error = dlerror();
	if ( error != NULL ) {
		DPRINTL(error);
		return NULL;
	}
	return shake_func;
}


TH_STRING getname ( thPlugin * plug) {
	TH_STRING (*info_func)();
	char * error;
	
	dlerror();
	info_func = (char *(*)(void)) dlsym( plug->handler, "getInfo" ) ;
	error = dlerror();
	if ( error != NULL ) {
		DPRINTL(error);
		return NULL;
	}
	return info_func();
}

int getsupport ( thPlugin * plug ) {
	int (*sup_func)();
	char * error;
	
	dlerror();
	sup_func = (int(*)(void)) dlsym( plug->handler, "getSupport" ) ;
	error = dlerror();
	if ( error != NULL ) {
		DPRINTL(error);
		return TH_PLUG_NONE;
	}
	return sup_func();
}


/* Add a new plugin to the list. The first argument is the last plugin of the list and
 * the result is a pointer to the new (last) plugin. If something goes wrong, NULL
 * is returned */
thPlugin * addPlugin ( thPlugin * list, char * filename ) {
	char * pname;
	size_t fnsize;
	thPlugin * newplug;
	
	/* Create new plugin entry */
	newplug = malloc(sizeof(thPlugin));
	if ( newplug == NULL ) return NULL;

	/* Create new plugin filename */
	fnsize = strlen(filename);
	pname = malloc(fnsize+1);
	if ( pname == NULL ) {
		thDestroyPlugin(newplug);
		return NULL;
	}
	pname = strncpy(pname, filename, fnsize);
	pname[fnsize]='\0';
	newplug->filename = pname;

	/* Get handler for this library */
	newplug->handler = dlopen(pname, RTLD_NOW);
	if ( newplug->handler == NULL ) {
		thDestroyPlugin(newplug);
		return NULL;
	}

	/* Get the shake function and save it's pointer */
	newplug->shakefunc = getshakefunc(newplug);
	if ( newplug->shakefunc == NULL ) {
		thDestroyPlugin(newplug);
		return NULL;
	}

	/* Get name of plugin from the file itself */
	newplug->name = getname(newplug);
	if ( newplug->name == NULL ) {
		newplug->name = malloc(13);
		strncpy(newplug->name, "Unknown Name", 13);
	}

	/* Get support actions of this plugin */
	newplug->support  = getsupport(newplug);
	if ( newplug->support == TH_PLUG_NONE ) {
		DPRINTF("Plugin \"%s\" does not support any actions.\n",filename);
		thDestroyPlugin(newplug);
		return NULL;
	}
	
	if ( list != NULL ) list->next = newplug;
	return newplug;
}


