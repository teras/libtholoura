####################################################
####################################################
##                                                ##
##  THIS FILE IS A MAKEFILE TEMPLATE FOR PLUGINS  ##
##                                                ##
####################################################
####################################################



#####################
# User defined part #
#####################

## Use the following variable to define any extra search path for libraries
#
#LIBPATH=-L/.../

## Use the following variable to define any extra search path for libraries
#
#INCPATH=-I/.../



######################################################
# General part - usually the defaults should suffice #
######################################################

## Library defines
#
LIBRARY=$(shell ls *.c | head -n 1 | sed -e 's/\.c$$//g')
#

## Program defines
#
CPP=gcc
RM=rm -f
CP=cp
MV=mv


## Compiler / linker defaults
#
#DEBUG= -g
CFLAGS = -Wall $(DEBUG) $(shell freetype-config --cflags) $(INCPATH) -I.. -ansi -pedantic
LDFLAGS =
LDLIBFLAGS = $(shell freetype-config --libs) $(LIBPATH) -lpng -ldl


######################################
# Automatically executed parts       #
# Usually the user should NOT change #
# anything below this line           #
# ####################################


LIBSRC=$(shell ls *.c)
LIBOBJS=$(LIBSRC:.c=.o)
LIBFILE=$(LIBRARY).so


.SUFFIXES:.o .c

.c.o:
	$(CPP) $(CFLAGS) -c -o $@ $?


all:$(LIBFILE)


$(LIBFILE):$(LIBOBJS)
	ld -shared $(LDLIBFLAGS) -o $@ $(LIBOBJS)
	strip $@
	chmod a-x $@

$(APPLICATION):$(APPLICATION).o
	$(CPP) $(LDFLAGS) -o $@ $@.o -L. -l$(LIBRARY)
	strip $@


clean:
	$(RM) *.o $(APPLICATION) $(LIBFILE) core

distclean:clean

