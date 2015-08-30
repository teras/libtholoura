#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN("Noise (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i;
	
	if ( ttext == NULL ) return;

	for ( i = 0; i < (ttext->height*ttext->width) ; i++ ){
		ttext->matrix[i] = ( (rand() % 150) + ttext->matrix[i]/2 ) % 256;
	}
}
