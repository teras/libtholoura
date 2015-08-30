#include "thplugin.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

INIT_PLUGIN("Sines (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)


void shakeIt ( thText * ttext, float distortion ) {
	int count;
	int x, y;
	int newy, oldy;
	int firstpoint;	/* the offset of the sinus function, measured in points */
	
	int offset;		/* The offset of the sinus, from top of the graph */
	int halfheight;	/* The half height of the sinus, measured in pixels */
	int width;	/* The width of a full circle measured in points */
	float xfactor;	/* Use this to convert x pixel values into radians */
	
	if ( ttext == NULL ) return;
	

	for ( count = 0 ; count < 4 ; count++ ) {
		
		halfheight = 3 + (rand()%((ttext->height/2)-5));
		offset = rand() % (ttext->height - (2*halfheight)-1) + halfheight ;
		width  = 10 + rand()%50;
		xfactor = (3.14159 * 2)/width;
		firstpoint = rand()%width;
/*		fprintf(stderr, "h=%i o=%i\n",height, offset); */
		
		oldy = offset + halfheight * sin(xfactor*firstpoint);
		for ( x = 0 ; x < ttext->width; x++) {
			newy = offset + halfheight * sin(xfactor*(x+firstpoint));
			if ( oldy < newy ) {
				for ( y = oldy ; y <= newy ; y++ ) {
					thPointAt(ttext, x, y ) = 255 - thPointAt(ttext, x, y );
				}
			}
			else {
				for ( y = newy ; y <= oldy ; y++ ) {
					thPointAt(ttext, x, y ) = 255 - thPointAt(ttext, x, y );
				}
			}
			oldy = newy;
		}
	}
}
