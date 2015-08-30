#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Random Walk (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i;
	TH_UCHAR mask;
	
	if ( ttext == NULL ) return;

	mask = 0;
	for ( i = 0; i < (ttext->height*ttext->width) ; i++ ){
		mask = (((rand()%2)?-1:1) + mask) % 256;
		ttext->matrix[i] = (mask + (ttext->matrix[i])/2 ) % 256;
	}
}
