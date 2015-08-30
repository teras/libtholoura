#ifndef __THPLUGIN_H
#define __THPLUGIN_H


/* tholoura data types */
#define TH_UINT		unsigned int
#define TH_UCHAR	unsigned char
#define TH_UCHARP	unsigned char *

#define TH_COLOR	TH_UINT
#define TH_COLORP	TH_COLOR *
#define TH_MATRIX	TH_UCHARP
#define TH_STRING	char *

/* Helper macro to properly conver the one dimensional
 * bitmap matrix to a 2-D matrix
 */
#define thPointAt(TTXT,X,Y)	((TTXT->matrix)[(Y)*TTXT->width+(X)])

/* Color macros */
#define thColorA(R,G,B,A)	( (((A)%256)<<24) + (((R)%256)<<16) + (((G)%256)<<8) + ((B)%256) )
#define thColor(R,G,B)		thColorA(R,G,B,255)

#define thColorAlpha(C)		((C&0xff000000)>>24)
#define thColorRed(C)		((C&0xff0000)>>16)
#define thColorGreen(C)		((C&0xff00)>>8)
#define thColorBlue(C)		( C&0xff)

/* Struct of the distorted text information */
typedef struct {
	TH_UINT width;	/* Matrix width */
	TH_UINT height;	/* Matrix height */
	TH_UINT top;	/* Topmost of drawn text */
	TH_UINT left;	/* Leftmost of drawn text */
	TH_UINT right;	/* Rightmost of drawn text */
	TH_UINT bottom;	/* Bottommost of drawn text */
	TH_UINT fontsize;	/* Font size (in pixels) */
	TH_UINT glyphs;		/* numer of glyphs */
	TH_STRING text;		/* Text */
	TH_MATRIX matrix;	/* Bitmap matrix. Here is where the actual image is stored. Evey byte is a point. This is a one dimensional matrix. Use the thPointAt macro above to properly convert it to 2D */
	TH_UINT colorsize;	/* Number of colors */
	TH_COLORP colors;	/* Color table of the image */
} thText;


/* Prototype of the main plugin function */
void shakeIt ( thText * ttext, float distortion );


#include <stdlib.h>
#include <string.h>
/* Use the following macro in order to properly initialize the plugin.
 * Do NOT use a semicolon at the end of this macro */
#define INIT_PLUGIN(X,Y)	    TH_STRING getInfo () { \
									TH_STRING name;\
									size_t size;\
									size = strlen(X);\
									name = malloc(size+1);\
									strncpy(name, (X), size+1);\
									return name;\
									}\
								\
								\
								int getSupport() {\
									return Y;\
								}

/* What does this plugin supprot */
#define TH_PLUG_NONE	0
#define TH_PLUG_BITMAP	1
#define TH_PLUG_COLOR	2


#endif /* __THPLUGIN_H */
