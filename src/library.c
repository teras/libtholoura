#include "tholoura.h"
#include "defaults.h"
#include "plugins.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>


#define TH_ERROR	1
#define TH_SUCCESS	0

#define STRINGSIZE	500
#define BUFFERSIZE	1000

TH_STRING trim( TH_STRING buffer) {
	TH_STRING start;
	TH_STRING finish;
	
	start = buffer;
	finish = buffer + strlen(buffer)-1;
	/* Find the beginning of the buffer */
	while ( (start!='\0') && (*start == ' ' || *start =='\t' || *start == '\n' || *start == '\r') )
		start++;
	/* Find the ending of the buffer */
	while ( (finish>=start) && (*finish == ' ' || *finish =='\t' || *finish == '\n' || *finish == '\r') )
		finish--;
	/* MArk ending */
	*(finish+1) = '\0';
	return start;
}


int load_config ( thLib * lib) {
	FILE *config;
	TH_STRING buffer;
	TH_STRING equal;	/* the position of the '=' character inside the config entry */
	TH_STRING key;	/* The real position of the key in buffer (without spaces) */
	TH_STRING value;	/* The real position of the key in buffer (without spaces) */
	thPlugin * lastplug;	/* The current (last) plugin */
	thPlugin * newplug;		/* The newly found plugin */
	
	buffer = malloc(BUFFERSIZE);
	if ( buffer == NULL ) {
		thDestroyLib(lib);
		return TH_ERROR;
	}
	
	/* Open tholoura.conf configuration file */
	config = fopen( THOLOURA_ETC, "rb" );
	if ( config == NULL ) {
		DPRINTS("Could not open configurtation file ");
		DPRINTS(THOLOURA_ETC);
		DPRINTS("\n");
		return TH_ERROR;
	}
	
	lib->plugins = NULL;
	lastplug = NULL;
	lib->plugsize=0;
	
	/* Start reading the config file */
	while ( (buffer = fgets(buffer, BUFFERSIZE, config)) != '\0' ) {
		if (buffer[0] == '#' ) continue;	 /* Ignore lines starting with # */
		/* Chech if an '=' char is found */
		equal=strchr(buffer, '=');
		if ( equal != NULL ) {
			*equal = '\0';
			/* seperate key from value */
			key = trim(buffer);
			value = trim(equal+1);
			/* check for ttfont entry */
			if ( strcmp(key, "fontfile") == 0 ) {
				strncpy (lib->fontname, value, STRINGSIZE);
				value[STRINGSIZE-1]='\0';
			}
			if ( strcmp(key, "plugin") == 0 ) {
				newplug = addPlugin(lastplug, value);
				if ( newplug == NULL ) {
					DPRINTS("Error while loading plugin ");
					DPRINTS(value);
					DPRINTS("\n");
				}
				else {
					if ( lib->plugins == NULL ) lib->plugins = newplug;
					lastplug = newplug;
					lib->plugsize++;
				}
			}
		}
	}
	
	/* set default ttfont entry, if none is found */
	if ( lib->fontname[0]=='\0' ) {
		DPRINTS("Font not found, resetting to default one.\n");
		strncpy (lib->fontname, TTF_FILENAME, STRINGSIZE);
		value[STRINGSIZE-1]='\0';
	}
	
	/* clean up & exit */
	free(buffer);
	fclose(config);
	return TH_SUCCESS;
}


thLib * thInitLib (){
	thLib * lib;
	
	/* reserve memory for the library */
	lib = malloc(sizeof(thLib));
	if ( lib == NULL ) return NULL;

	/* reserve memory for the font name */
	lib->fontname = malloc(STRINGSIZE);
	if ( lib->fontname == NULL ) {
		thDestroyLib(lib);
		return NULL;
	}
	lib->fontname[0]='\0';

	/* load config */
	if ( load_config(lib) != TH_SUCCESS ) {
		thDestroyLib(lib);
		return NULL;
	}
	
	/* initialize random number generator */
	srand(time(NULL));
					
	return lib;
}



void thDestroyLib ( thLib * lib) {
	thPlugin *plug;
	thPlugin *nextplug;
	
	if ( lib != NULL ) {
		if ( lib->fontname != NULL ) free(lib->fontname);
		plug = lib->plugins;
		while ( plug != NULL) {
			nextplug = plug->next;
			free(plug);
			plug = nextplug;
		}
		free(lib);
	}
}

