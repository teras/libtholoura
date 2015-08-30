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
LIBRARY=tholoura


## Program defines
#
CC=gcc
RM=rm -f
CP=cp
MV=mv

## Library debugging messages
#
LIBDEBUG=-DDEBUG

## Binary debug info
#DEBUG=-g

## Compiler / linker defaults
#
CFLAGS = $(LIBDEBUG) $(DEBUG) -DETC=\"${ETC}\" -Wall $(shell freetype-config --cflags) $(INCPATH) -I../plugins -ansi -pedantic
LDFLAGS =
LDLIBFLAGS = $(DEBUG) $(shell freetype-config --libs) $(LIBPATH) -lpng -ldl


## Failsafe environmental variables, in order for the library
## to know the desired default paths. This should be already defined
## one directory level in the Makefile above. It exists here only for
## security reasons
#
ifeq ($(ETC),)
	ETC=/etc
endif



###############################################################
# Automatically executed parts                                #
# Usually the user should NOT change anything below this line #
# #############################################################


LIBSRC=$(shell ls *.c)
LIBOBJS=$(LIBSRC:.c=.o)
LIBFILE=lib$(LIBRARY).so


.SUFFIXES:.o .c

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $?


all:$(LIBFILE)


$(LIBFILE):$(LIBOBJS)
	ld -shared $(LDLIBFLAGS) -o $@ $(LIBOBJS)
	strip $@
	chmod a-x $@

clean:
	$(RM) *.o $(APPLICATION) $(LIBFILE) core

distclean:clean

