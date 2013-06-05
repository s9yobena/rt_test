/* USAGE message from ft_tools */
#ifndef CMDLPARSER_H
#define CMDLPARSER_H

#include <stdio.h>
#include <cstdlib>
#include <getopt.h>
#include <string.h>
#include "rttypes.h"

#define MAX_RT_TEST_NAME 100

#define USAGE							\
	"rt_launch-test [--rtg <rt-config-test.rtg>]\n" \
	"   --rtg: real-time test config file \n " \
	"   One of the following schedulability tests:  \n " \
	"   --rt-test  \n " \
	""


class CmdlParser {
 public :
	char rtConfigTestName[MAX_RT_TEST_NAME];
	RtTestName rtTestName;


  CmdlParser(int, char**);
  ~CmdlParser();


};

#endif
