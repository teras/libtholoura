#include "thplugin.h"
#include <stdlib.h>
#include <math.h>

#define pow2(X)		(1<<(X))

INIT_PLUGIN("Plasma (C) 2004 Panayotis Katsaloulis panayotis@panayotis.com under GNU GPL", TH_PLUG_BITMAP)

#define array(X,Y)	plasma[(X)+(Y)*pwidth]

void shakeIt ( thText * ttext, float distortion ) {
	int sizex, sizey;
	int pwidth, pheight;
	int x,y;
	int average, roughness, color;
	int p;
	int _2_p, _2_pp1;

	int matsize;
	TH_MATRIX plasma;
	
	if ( ttext == NULL ) return;
	
	matsize = ttext->width*ttext->height;
	plasma = malloc(matsize);
	if ( plasma == NULL ) return;
	
	
	pwidth = ttext->width;
	sizex = pwidth - 1;
	
	pheight = ttext->height;
	sizey = pheight - 1;
	roughness = 2;
	
	array(0,0) = rand() % 256;
	array(sizex,0) = rand() % 256;
	array(0,sizey) = rand() % 256;
	array(sizex,sizey) = rand() % 256;

	
	for ( p = (int)log(sizex) / log(2); p >= 0 ; p-- ) {
		_2_p = pow2(p);
		_2_pp1 = pow2(p+1);
		for ( x = 0; x <= sizex ; x += _2_p ) {
			for ( y = 0; y <= sizey ; y += _2_p ) {
				if ( (x % _2_pp1 == 0) && (y % _2_pp1 == 0) ) ;
				else if ( (x % _2_pp1) == 0 ) {
					average = ( array(x, y +_2_p) + array(x, y - _2_p)) /2;
					color = average + roughness * ( (rand()%2)?-1:1);
					array(x,y) = array(x,y) + color;
				}
				else if ( (y % _2_pp1) == 0 ) {
					average = ( array(x + _2_p, y) + array (x - _2_p, y))/2;
					color = average + roughness * ( (rand()%2)?-1:1);
					array(x,y) = array(x,y)+color;
				}
				else if ( (x % _2_pp1) > 0 && ( y % _2_pp1 > 0 ) ) {
					average = array(x + _2_p, y + _2_p) + array(x + _2_p, x - _2_p) + array(x - _2_p, x + _2_p) + array(x - _2_p, y - _2_p);
					color = average + roughness * ( (rand()%2)?-1:1);
					array(x,y) = array(x,y)+color;
				}
			}
		}
	}

	for ( x = 0 ; x < matsize ; x++ ) {
		ttext->matrix[x] = (3*plasma[x]/4 + ttext->matrix[x]/2)%256;
	}
}

/* 
� randomly choose the rectangle�s corners
array(0, 0) = RND * number_of_colors
array(size, 0) = RND * number_of_colors
array(0, size) = RND * number_of_colors
array(size, size) = RND * number_of_colors
� go through the array, decreasing the interval size every time
FOR p = LOG(size) / LOG(2) TO 0 STEP -1
  FOR x = 0 TO size STEP 2 ^ p
     FOR y = 0 TO size STEP 2 ^ p
        IF x MOD 2 ^ (p + 1) = 0 AND y MOD 2 ^ (p + 1) = 0 GOTO nxt
        IF x MOD 2 ^ (p + 1) = 0 THEN
          average = (array(x, y + 2 ^ p) + array(x, y - 2 ^ p)) / 2
          color = average + roughness * (RND - .5)
          array(x, y) = color: GOTO nxt
        END IF
        IF y MOD 2 ^ (p + 1) = 0 THEN
          average = (array(x + 2 ^ p, y) + array(x - 2 ^ p, y)) / 2
          color = average + roughness * (RND - .5)
          array(x, y) = color: GOTO nxt
        END IF
        IF x MOD 2 ^ (p + 1) > 0 AND y MOD 2 ^ (p + 1) > 0 THEN
          v1 = array(x + 2 ^ p, y + 2 ^ p)
          v2 = array(x + 2 ^ p, x - 2 ^ p)
          v3 = array(x - 2 ^ p, x + 2 ^ p)
          v4 = array(x - 2 ^ p, y - 2 ^ p)
          average = (v1 + v2 + v3 + v4) / 4
          color = average + roughness * (RND - .5)
          array(x, y) = color: GOTO nxt
        END IF
        nxt:
    NEXT y
  NEXT x
NEXT p
� go through the array, plotting the points
FOR x = 0 TO size
      FOR y = 0 TO size
           PSET (x, y), array(x, y)
      NEXT y
NEXT x

*/	
