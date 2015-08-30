#ifndef __TH_DEFAULTS_H
#define __TH_DEFAULTS_H

#ifndef ETC
/* This variable should already be defined in the toplevel Makefile
 * It is here only for failsafe reasons. */
#define ETC			"/etc"
#endif

#define THOLOURA_ETC	ETC "/tholoura.conf"

#ifdef DEBUG
#define	DPRINTF(type,what)  fprintf(stderr,type,what);fflush(stderr)
#else
#define DPRINTF(type,what)
#endif

#define DPRINTS(what)       DPRINTF("%s",what)
#define DPRINTL(what)       DPRINTF("%s\n",what)

#define TTF_FILENAME	"/usr/share/fonts/truetype/freefont/FreeSans.ttf"

#endif /* __TH_DEFAULTS_H */
