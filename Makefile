# Makefile copied from ft_tools and modified

# ##############################################################################
# User variables

# user variables can be specified in the environment or in a .config file
# -include .config

# Where is the LITMUS^RT userspace library source tree?
LIBLITMUS ?= ../liblitmus

# Include default configuration from liblitmus
# Liblitmus must have been built before rt_schedtest can be built.
include ${LIBLITMUS}/inc/config.makefile

# Set our configuration 
CFLAGS     = -Wall -Werror -g
LDFLAGS    +=  -fopenmp  	
CPPFLAGS  += -Iinclude/ -fopenmp -g
CC         = /usr/bin/g++

# all sources
vpath %.c src/
vpath %.cpp src/


# ##############################################################################
# Targets

all = rt_config-test rt_test rt_efficacy-test rt_extra-cxs

.PHONY: all clean TAGS
all: ${all}
clean:
	rm -f ${all} *.o *.d
	rm -f TAGS


obj-rt_config-test = rt_config-test.o taskset.o task.o  launchtestparam.o launchtest.o tasksetgenerator.o tasksetparam.o cmdlparser.o

obj-rt_test = rt_test.o  cmdlparser.o taskset.o task.o launchtestparam.o testresults.o tasksetgenerator.o tasksetparam.o

obj-rt_efficacy-test = rt_efficacy-test.o  cmdlparser.o taskset.o task.o launchtestparam.o testresults.o tasksetgenerator.o tasksetparam.o

obj-rt_extra-cxs = rt_extra-cxs.o  cmdlparser.o taskset.o task.o launchtestparam.o testresults.o tasksetgenerator.o tasksetparam.o

rt_config-test: ${obj-rt_config-test}

rt_test: ${obj-rt_test}

rt_efficacy-test: ${obj-rt_efficacy-test}

rt_extra-cxs: ${obj-rt_extra-cxs}


# Emacs Tags
TAGS:
	@echo TAGS
	@find . -regex ".*\.[cChH]\(pp\)?" -print | etags -
