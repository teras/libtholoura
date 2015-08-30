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

## Application defines
#
APPLICATION=$(shell ls *.c | head -n 1 | sed -e 's/\.c$$//g')
#

## Program defines
#
CC=gcc
RM=rm -f
CP=cp
MV=mv
AWK=gawk


## Compiler / linker defaults
#
#DEBUG= -g
CFLAGS = -Wall $(DEBUG) -I../src -I../plugins -ansi -pedantic
LDFLAGS = $(shell freetype-config --libs) $(LIBPATH) -L../src -ltholoura -lpng -ldl


######################################
# Automatically executed parts       #
# Usually the user should NOT change #
# anything below this line           #
# ####################################


APPSRC=$(shell ls *.c)
APPOBJS=$(APPSRC:.c=.o)


.SUFFIXES:.o .c

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $?


all:$(APPLICATION)


$(APPLICATION):$(APPOBJS)
	$(CC) $(LDFLAGS) -o $@ $(APPOBJS)
	strip $@


clean:
	$(RM) $(APPOBJS) $(APPLICATION) core

distclean:clean

