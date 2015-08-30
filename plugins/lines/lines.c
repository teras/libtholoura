#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Lines (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	
	if ( ttext == NULL ) return;

	if ( rand()%2 ) {
		for ( i = 0 ; i < ttext->height; i=i+3) {
			for ( j = 0 ; j < ttext->width; j++ ) {
				thPointAt(ttext,j,i) = 255 - thPointAt(ttext,j,i);
			}
		}
	}
	else {
		for ( j = 0 ; j < ttext->width; j=j+3 ) {
			for ( i = 0 ; i < ttext->height; i++) {
				thPointAt(ttext,j,i) = 255 - thPointAt(ttext,j,i);
			}
		}
	}

}
