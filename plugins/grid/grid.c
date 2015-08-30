#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Grid (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;

	if ( ttext == NULL ) return;
	for ( i = 2 ; i < ttext->height; i=i+5) {
		for ( j = 0 ; j < ttext->width; j++ ) {
			thPointAt(ttext,j,i)= 255 - thPointAt(ttext,j,i);
		}
	}
	for ( i = 2 ; i < ttext->width; i=i+5) {
		for ( j = 0 ; j < ttext->height; j++ ) {
			thPointAt(ttext,i,j) = 255 - thPointAt(ttext,i,j);
		}
	}
}
