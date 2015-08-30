#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN ("Wipe out (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under the GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	int step;
	
	if ( ttext == NULL ) return;

	step = 2 + rand()%3;
	for ( i = 0 ; i < ttext->height; i+=step) {
		for ( j = 0 ; j < ttext->width; j++) {
			thPointAt(ttext,j,i) = 0;
		}
	}

	step = 2 + rand()%3;
	for ( i = 0 ; i < ttext->width; i+=step) {
		for ( j = 0 ; j < ttext->height; j++) {
			thPointAt(ttext,i,j) = 0;
		}
	}
}

