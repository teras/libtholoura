#ifndef __THOLOURA_H
#define __THOLOURA_H

#include "thplugin.h"
#include <stdio.h>

#define TH_CHARSET_NUMERALS		1
#define TH_CHARSET_LOWCASE		2
#define TH_CHARSET_UPPERCASE	4
#define TH_CHARSET_MASK			7

typedef struct thPlugin {
	TH_STRING name;
	TH_STRING filename;
	TH_UINT support;
	void * handler;
	void (*shakefunc)(thText *, float);
	struct thPlugin * next;
} thPlugin;
	

typedef struct {
	char * fontname;
	thPlugin * plugins;
	int plugsize;
} thLib;


thLib * thInitLib ();
void thDestroyLib ( thLib * lib);

thText * thInitRandomText ( thLib * lib, int length, int charset, int fontsize, int border);
thText * thInitText ( thLib * lib, char * text, int fontsize, int border );
void thDestroyText ( thLib * lib, thText * ttext );

void thShakeText ( thLib * lib, thText * ttext, int type );

void thGetPNG (thLib *lib, thText *ttext, FILE* file);

#endif /* __THOLOURA_H */
