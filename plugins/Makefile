ifneq ($(shell which mawk),)
	AWK=mawk
else
ifneq ($(shell which gawk),)
	AWK=gawk
else
	AWK=awk
endif
endif

all:
	for i in `ls -l | grep ^d | ${AWK} '{print $$8}'` ; do \
		(cd $$i ; if [ -f Makefile ] ; then make all ; fi) ;\
	done

distclean:
	for i in `ls -l | grep ^d | ${AWK} '{print $$8}'` ; do \
		(cd $$i ; if [ -f Makefile ] ; then make distclean ; fi) ;\
	done
