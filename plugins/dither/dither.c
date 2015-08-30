#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN ("Dither (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)


void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	TH_UCHAR val;
	
	if ( ttext == NULL ) return;

	for ( i = 0 ; i < ttext->height ; i+=2 ) {
		for ( j = 0 ; j < ttext->width ; j+=2 ) {
			thPointAt(ttext,j,i) = 255 - thPointAt(ttext,j,i);
		}
	}
	for ( i = 1 ; i < ttext->height ; i+=2 ) {
		for ( j = 1 ; j < ttext->width ; j+=2 ) {
			val = thPointAt(ttext,j,i);
			if ( val < 128 ) { 
				thPointAt(ttext,j,i) = 255 - val;
			}
		}
	}
}

