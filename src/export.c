#include <png.h>

#include "tholoura.h"
#include "defaults.h"

void thGetPNG (thLib *lib, thText * ttext, FILE * out) {
	png_structp png_ptr;
	png_infop info_ptr ;
	png_colorp palette;
	png_bytep * row_pointers;
	TH_COLOR col;
	int i;
	
	if (!out) return;
	if ( lib == NULL || ttext == NULL ) return;
	
	/* Create PNG writing structure */
	png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, png_voidp_NULL, png_error_ptr_NULL, png_error_ptr_NULL);
	if (!png_ptr) return;

	/* Create PNG info structure */
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL); 
		return;
	}
	
	/* Setup error handling */
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr); 
		return;
	}
	
	/* Set the contents info of the PNG */
	png_set_IHDR(png_ptr, info_ptr, ttext->width, ttext->height, 8, PNG_COLOR_TYPE_PALETTE, PNG_INTERLACE_ADAM7, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	/* Create the palette from the data */
	palette = (png_colorp)png_malloc(png_ptr, ttext->colorsize * sizeof (png_color));
	for (i=0; i < ttext->colorsize; i++) {
		col = ttext->colors[i];
		palette[i].red = thColorRed(col);
		palette[i].green = thColorGreen(col);
		palette[i].blue = thColorBlue(col);
	}
	png_set_PLTE(png_ptr, info_ptr, palette, ttext->colorsize);


	/* Inform about the bitmap data */
	row_pointers = png_malloc(png_ptr, ttext->height*sizeof(png_bytep));
	for ( i=0; i < ttext->height; i++)
		row_pointers[i]= (ttext->matrix + i*ttext->width);
	png_set_rows(png_ptr, info_ptr, row_pointers);

	/* Initialize writing */
	png_init_io(png_ptr, out);
	
	/* Write image to file */
	png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

	png_destroy_write_struct(&png_ptr, &info_ptr);

}
