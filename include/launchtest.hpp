#ifndef LAUNCH_TEST_HPP
#define LAUNCH_TEST_HPP

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include "cstring"
#include <iostream>
#include "cmdlparser.h"

using namespace std;

class LaunchTest {
  
private:
  LaunchTest();
  LaunchTest(const LaunchTest&);
  LaunchTest& operator= (const LaunchTest&);
  static LaunchTest* launchTestInstance;
  
  void initLaunchTest(char*);
  char launchTestName[20];
  char launchTestNameOption[25];
  RtTestName rtTestName;

public:
  static LaunchTest* getInstance();
  void callLaunchTest(char*);
  void setParameters(const CmdlParser&);
};

#endif
