#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Stripes (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i;
	
	if ( ttext == NULL ) return;

	for ( i = 2; i < (ttext->height*ttext->width) ; i=i+4 ){
		ttext->matrix[i] = 255 - ttext->matrix[i];
	}
	for ( i = 4; i < (ttext->height*ttext->width) ; i=i+11 ){
		ttext->matrix[i] = 255 - ttext->matrix[i];
	}
}
