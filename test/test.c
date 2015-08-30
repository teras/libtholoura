#include	"tholoura.h"
#include <stdio.h>
#include <stdlib.h>


int main( int argc, char ** argv  )
{
	thText *ttext;
	thLib *tlib;
	
	tlib = thInitLib();
	if ( tlib == NULL ) return 0;
	fprintf(stderr, "Font used:%s\n", tlib->fontname);
	
	ttext = thInitRandomText ( tlib, 8, TH_CHARSET_NUMERALS, 64, 4);
/*	ttext = thInitRandomText ( tlib, 8, TH_CHARSET_UPPERCASE|TH_CHARSET_NUMERALS|TH_CHARSET_LOWCASE, 64, 4); */
	fprintf(stderr, "Text to produce: %s\n", ttext->text);

	thShakeText ( tlib, ttext, 0);
	thGetPNG ( tlib, ttext, stdout);
	thDestroyText ( tlib, ttext );
	thDestroyLib(tlib);

	return 0;
}
