#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN ("Dizzy  (C) 2004 Panayotis Katsaloulis http://www.panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	int d;
	
	d = 0;
	
	if ( ttext == NULL ) return;

	for ( i = 2 ; i < ttext->height; i=i+5) {
		for ( j = 0 ; j < ttext->width; j++ ) {
			d++;
			thPointAt(ttext,j,i-d%2) = 255 - thPointAt(ttext,j,i-d%2);
		}
	}
	d = 0;
	for ( i = 2 ; i < ttext->width; i=i+5) {
		for ( j = 0 ; j < ttext->height; j++ ) {
			d++;
			thPointAt(ttext,i-d%2, j) = 255 - thPointAt(ttext, i-d%2, j);
		}
	}
}

