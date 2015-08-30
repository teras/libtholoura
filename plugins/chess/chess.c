#include "thplugin.h"
#include <stdlib.h>

INIT_PLUGIN ("Chess (C) 2004 Panayotis Katsaloulis http://www.panayotis.com under the GNU GPL", TH_PLUG_BITMAP)

void shakeIt ( thText * ttext, float distortion ) {
	int i,j;
	int x,y;
	
	if ( ttext == NULL ) return;

	for ( i = 0 ; i < ttext->height; i++) {
		for ( j = 0 ; j < ttext->width; j++ ) {
			x = i%20>9;
			y = j%20>9;
			if ( x&&y ) {
				thPointAt(ttext,j,i) = 255 - thPointAt(ttext,j,i);
			}
		}
	}
}

