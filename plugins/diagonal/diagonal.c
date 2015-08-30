#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Diagonals (C) 2004 Panayotis Katsaloulis http://www.panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int x,y;
	int checkpoint;
	
	if ( ttext == NULL ) return;

	checkpoint = 2 + rand()%3;

	for ( y = 0; y < ttext->height; y++ ) {
		for ( x = 0 ; x < ttext->width; x++) {
			if ( !((x+y)%checkpoint) ) {
				thPointAt(ttext,x,y) = 255 - thPointAt(ttext,x,y);
			}
		}
	}
}
