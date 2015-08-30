#include "tholoura.h"
#include "defaults.h"

#include <ft2build.h>
#include FT_FREETYPE_H


TH_COLORP init_colors (thText * ttext) {
	TH_COLORP colors;
	int i;

	colors=malloc(256*sizeof(TH_COLOR));
	if ( colors == NULL ) return NULL;

	for ( i = 255 ; i >= 0 ; i-- ) {
		colors[255-i] = thColor(i, i, i);
	}
	ttext->colors = colors;
	ttext->colorsize = 256;
	return colors;
}


/* Copy bitmap from the FreeType bitmap to the native matrix data */
void draw_bitmap ( thText * ttext, FT_Bitmap * bitmap, int left, int top ) {
	int x, y;
	int bitmappos, thpos;
	int right, bottom;

	bitmappos = 0;
	thpos = left + top * ttext->width;	/* Find the initial position of the glyph inside the matrix */
	right = bitmap->width + left;	/* Find right edge of the glyph */
	bottom = bitmap->rows + top;	/* Find bottom edge of the glyph */
	
	/* Find new text borders */
	if ( ttext->left > left ) 
		ttext->left = left;
	if ( ttext->right < right ) 
		ttext->right = right;
	if ( ttext->top > top ) 
		ttext->top = top;
	if ( ttext->bottom < bottom ) 
		ttext->bottom = bottom;
	
	/* "Draw" the current glyph */
	for ( y = 0 ; y < bitmap->rows ; y++ ) {
		for ( x = 0 ; x < bitmap->width ; x++ ) {
			ttext->matrix[thpos+x] = bitmap->buffer[bitmappos+x]; 
		}
		bitmappos += bitmap->pitch;
		thpos += ttext->width;
	}
}


void cropEdges ( thText * ttext, int border ) {
	TH_MATRIX new_mat;
	int txtwidth, txtheight;
	int new_matwidth, new_matheight;
	int new_matsize;
	int old_matwidth;
	int old_matpos, new_matpos;
	int old_ycol, new_ycol;
	int x, y;
	
	/* First check if border size is sane */
	if ( border < 0 ) return;

	/* Find the text size */
	txtwidth  = ttext->right  - ttext->left + 1;
	txtheight = ttext->bottom - ttext->top + 1;
	new_matwidth  = txtwidth  + 2*border;
	new_matheight = txtheight + 2*border;
	new_matsize = new_matwidth*new_matheight;
	
	/* Reserve memory for the new matrix */
	new_mat = malloc(new_matsize);
	if ( new_mat == NULL ) {
		return ;
	}
	memset(new_mat, 0, new_matsize);

	old_matwidth = ttext->width;
	/* Find the initial position of text for each matrix */
	old_matpos = ttext->top * ttext->width + ttext->left;
	new_matpos = border * new_matwidth + border;

	/* Copy new matrix to the old one */
	for ( y = 0 ; y < txtheight ; y++) {
		old_ycol = y*old_matwidth + old_matpos;
		new_ycol = y*new_matwidth + new_matpos;
		for ( x = 0; x < txtwidth ; x++ ) {
			new_mat[new_ycol+x] = ttext->matrix[old_ycol+x];
		}
	}

	/* Free resources */
	free (ttext->matrix);
	/* Set new matrix values */
	ttext->width  = new_matwidth;
	ttext->height = new_matheight;
	ttext->top  = border;
	ttext->left = border;
	ttext->right  = border+txtwidth;
	ttext->bottom = border+txtheight;
	ttext->matrix = new_mat;
}



thText * thInitRandomText ( thLib * lib, int length, int charset, int fontsize, int border){
	TH_STRING text;
	TH_STRING chartable;
	int tablesize;
	int offset;
	int i;

	if ( (charset&TH_CHARSET_MASK) == 0 ) {
		DPRINTL("Charset not valid.");
		return NULL;
	}
	
	tablesize = 0;
	if ( charset&TH_CHARSET_NUMERALS ) tablesize += 10;
	if ( charset&TH_CHARSET_LOWCASE ) tablesize += 26;
	if ( charset&TH_CHARSET_UPPERCASE ) tablesize += 26;

	chartable = malloc(tablesize);
	if ( chartable == NULL ) return NULL;
	
	/* Create possible character set tables */
	offset = 0;
	if ( charset&TH_CHARSET_NUMERALS ) {
		for ( i = 0 ; i < 10 ; i++) {
			chartable[offset+i] = i+'0';
		}
		offset += 10;
	}
	if ( charset&TH_CHARSET_LOWCASE ) {
		for ( i = 0 ; i < 26 ; i++) {
			chartable[offset+i] = i+'a';
		}
		offset += 26;
	}
	if ( charset&TH_CHARSET_UPPERCASE ) {
		for ( i = 0 ; i < 26 ; i++) {
			chartable[offset+i] = i+'A';
		}
	}
	
	text = malloc(length+1);
	if ( text == NULL ) {
		free(chartable);
		return NULL;
	}
	
	for ( i = 0 ; i < length ; i++ ) {
		text[i] = chartable[rand()%tablesize];
	}
	text[length]='\0';
	free(chartable);
	return thInitText (lib, text, fontsize, border);
}


/* WARNING: probably we SHOULD define the text length */
thText * thInitText ( thLib * lib, char * text, int fontsize, int border ){
	/* Initialization variables */
	thText * ttext;
	int count, matrixsize;
	int i;
	/* Drawing variables */
	FT_Library library;
	FT_Face face;
	FT_GlyphSlot slot ;
	int error, pen_x, pen_y;
	
	/* Return if library is not initialized */
	if ( lib == NULL ) return NULL;

	/* Reserve memory for thText structure */
	ttext = malloc(sizeof(thText));
	if ( ttext == NULL ) return NULL;

	/* Create a matrix to store the dispayed text */
	count = strlen ( text );
	ttext->width = (count+2)*fontsize;	/* fontsize*2 should be safe bet */
	ttext->height = fontsize*2;	/* Again, *2 should be a safe bet */
	matrixsize = ttext->width * ttext->height;
	ttext->left = fontsize;
	ttext->right = fontsize;
	ttext->top = fontsize;
	ttext->bottom = fontsize;

	ttext->fontsize = fontsize;
	ttext->glyphs = count;
	ttext->text = NULL;
	ttext->matrix = NULL;

	/* Reserve memory for text string */
	ttext->text = malloc(count+1);
	if ( ttext->text == NULL ) {
		thDestroyText ( lib, ttext );
		return NULL;
	}

	/* Reserve memory for bit matrix structure */
	ttext->matrix = malloc(matrixsize);
	if ( ttext->matrix == NULL ) {
		thDestroyText ( lib, ttext );
		return NULL;
	}

	/* Reserve memory for color structure */
	if ( init_colors(ttext) == NULL ) {
		thDestroyText ( lib, ttext );
		return NULL;
	}
	
	/* Copy text to memory */
	strncpy ( ttext->text, text, count);
	ttext->text[count]='\0';

	/* Clear matrix */
	memset(ttext->matrix,0,matrixsize);

	/* End of initialization */
	/* Begin of drawing */
	
	/* Initialize FreeType library */
	error = FT_Init_FreeType( &library );
	if ( error ) {
		thDestroyText ( lib, ttext );
		DPRINTL("Could not initialize FT library");
		return NULL;
	}
	
	/* Load font from disk */
	error = FT_New_Face( library, lib->fontname, 0, &face );
	if ( error ) {
		thDestroyText ( lib, ttext );
		DPRINTL("Could not open font face");
		return NULL;
	}
	slot = face->glyph;
	/* Set font size */
	error = FT_Set_Pixel_Sizes( face, 0, ttext->fontsize );
	if ( error ) {
		thDestroyText ( lib, ttext );
		DPRINTS("Could not set pixel size");
		return NULL;
	}

	/* Draw character by character to the selected matrix */
	pen_x = ttext->fontsize;
	pen_y = ttext->fontsize;
	for ( i = 0 ; i < ttext->glyphs ; i++ ) {
		error = FT_Load_Char( face, ttext->text[i], FT_LOAD_RENDER );
		if (error) continue;
		/* Calculate new diemnsions */
		draw_bitmap( ttext, &slot->bitmap, pen_x + slot->bitmap_left, pen_y - slot->bitmap_top );
		pen_x += slot->advance.x >> 6;
		pen_y += slot->advance.y >> 6;
	}
	/* Drop unneeded space */
	cropEdges ( ttext, border );
	return ttext;
}


void thDestroyText ( thLib * lib, thText * ttext ) {
	if ( ttext != NULL ) {
		if ( ttext->text != NULL ) 
			free ( ttext->text );
		if ( ttext->matrix != NULL ) 
			free ( ttext->matrix );
		if ( ttext->colors != NULL ) {
			free(ttext->colors);
		}
		free ( ttext );
	}
}

