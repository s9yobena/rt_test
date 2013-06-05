#include "launchtest.hpp"
#include <cstdio>
#include <cstring>

// struct plugin_name {
//   const char *name;
//   const char *launchtestname;
// };

// static struct plugin_name plugin_table [] = {
  
//   {"SAMPLE-TEST","rt-test"},
//   {"EFFICACY-TEST","rt-efficacy-test"},
//   {"EXTRA-CXS-TEST","rt-extra-cxs"},
// };


LaunchTest::LaunchTest() {
}

LaunchTest* LaunchTest::launchTestInstance = 0;

LaunchTest* LaunchTest::getInstance() {
  
  if (!launchTestInstance) {
    launchTestInstance = new LaunchTest();
  }
  return launchTestInstance;
}


void LaunchTest::callLaunchTest(char *rtConfigTestParamFile) {

  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  // Experiment process
  if (pid == 0) {

	  switch (rtTestName) {
	  case RT_TEST:
		  execl( "./rt_test","rt_test", 
			 "--rtg", rtConfigTestParamFile,
			 (char *) NULL );
		  perror( "execl()" );
		  exit(EXIT_FAILURE);
      
	  case RT_EFFICACY_TEST:
		  execl( "./rt_efficacy-test","rt_efficacy-test", 
			 "--rtg", rtConfigTestParamFile,
			 (char *) NULL );
		  perror( "execl()" );
		  exit(EXIT_FAILURE);

	  case RT_EXTRA_CXS:
		  execl( "./rt_extra-cxs","rt_extra-cxs", 
			 "--rtg", rtConfigTestParamFile,
			 (char *) NULL );
		  perror( "execl()" );
		  exit(EXIT_FAILURE);
	  }
  } 
}

void LaunchTest::setParameters(const CmdlParser& cmdlParser) {
  rtTestName = cmdlParser.rtTestName;
}
