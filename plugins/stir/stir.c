#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Stir (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	int maxstir, curstir, laststir;

	if ( ttext == NULL ) return;

	maxstir = ttext->top+2;
	/* Stir horizontal */
	for ( i = 0 ; i < ttext->width; i++ ) {
		curstir = i%maxstir;
		if ( curstir != 0 ) {
			laststir = ttext->height - curstir;
			for ( j = 0 ; j < laststir ; j++ ) {
				thPointAt(ttext,i, j) = thPointAt(ttext,i,j+curstir);
			}
		}
	}
	for ( i = 0 ; i < ttext->height; i++ ) {
		curstir = i%maxstir;
		if ( curstir != 0 ) {
			laststir = ttext->width - curstir;
			for ( j = 0 ; j < laststir ; j++ ) {
				thPointAt(ttext,j,i) = thPointAt(ttext,j+curstir,i);
			}
		}
	}

}
