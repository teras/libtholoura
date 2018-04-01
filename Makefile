######################
# User defined paths #
######################

PREFIX=/usr/local
ETC=/etc
FONTFILE=font/font.ttf


####################################
# OK THANK YOU, JUST SAVE AND EXIT #
####################################




# Variables automatically computed
# 
DISTFILENAME=$(shell cd .. ; ls -d libtholoura* | grep -v tar )
ETCFILE=${ETC}/tholoura.conf
LIBDIR=${PREFIX}/lib
PLUGINDIR=${LIBDIR}/tholoura

#CP=ln -s
CP=cp

all:
	cd doc && (if [ -f Makefile ] ; then make all ; fi) 
	cd plugins && (if [ -f Makefile ] ; then make all ; fi) 
	cd src && (if [ -f Makefile ] ; then make all ETC=${ETC}; fi) 
	cd test && (if [ -f Makefile ] ; then make all ; fi) 

distclean:
	cd doc && (if [ -f Makefile ] ; then make distclean ; fi) 
	cd plugins && (if [ -f Makefile ] ; then make distclean ; fi) 
	cd src && (if [ -f Makefile ] ; then make distclean ; fi) 
	cd test && (if [ -f Makefile ] ; then make distclean ; fi) 
	rm -f $(DISTFILENAME).tar.bz2
	rm -f result.png

clean:distclean

dist:distclean
	cd .. && tar jcvf $(DISTFILENAME).tar.bz2 $(DISTFILENAME) && mv $(DISTFILENAME).tar.bz2 $(DISTFILENAME)

testrun:test/test src/libtholoura.so
	LD_LIBRARY_PATH=src test/test >result.png

testdiplay:test/test src/libtholoura.so
	LD_LIBRARY_PATH=${LIBDIR} test/test >result.png
	display result.png

test/test:
	cd test && (if [ -f Makefile ] ; then make all ; fi) 

src/libtholoura.so:
	cd test && (if [ -f Makefile ] ; then make all ; fi)

install:all
	@echo
	@echo "Installed paths:"
	@echo "****************"
	@echo
	@echo " PREFIX=${PREFIX}"
	@echo " ETC=${ETC}"
	@echo
	@echo " Default font file: ${FONTFILE}"
	@echo
	@echo "If you want to change any of these settings, please edit the Makefile"
	@echo -n "Press [RETURN] to start installation"
	@read
	make uninstall
	mkdir -p ${PLUGINDIR}
	for i in `find plugins -name *.so` ; do ${CP} `pwd`/$$i ${PLUGINDIR}; done
	mkdir -p ${ETC}
	echo  >${ETCFILE} "# Use the following font file in order to render glyphs"
	echo >>${ETCFILE} "fontfile=${PLUGINDIR}/font.ttf"
	echo >>${ETCFILE}
	echo >>${ETCFILE} "# List of available plugins"
	cd ${PLUGINDIR} ; for i in `ls *.so` ; do echo >>${ETCFILE} "plugin=${PLUGINDIR}/$$i" ; done
	${CP} "${FONTFILE}" ${PLUGINDIR}/font.ttf
	${CP} `pwd`/src/libtholoura.so ${LIBDIR}

uninstall:
	rm -rf ${PLUGINDIR}
	rm -f ${LIBDIR}/libtholoura.so
	rm -f ${ETCFILE}
