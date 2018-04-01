ifneq ($(shell which mawk 2>/dev/null),)
	AWK=mawk
else
ifneq ($(shell which gawk 2>/dev/null),)
	AWK=gawk
else
	AWK=awk
endif
endif

all:
	for i in `ls -d */` ; do \
		(cd $$i ; if [ -f Makefile ] ; then make all ; fi) ;\
	done

distclean:
	for i in `ls -d */` ; do \
		(cd $$i ; if [ -f Makefile ] ; then make distclean ; fi) ;\
	done
