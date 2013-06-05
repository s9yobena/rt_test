#ifndef LAUNCH_TEST_PARAM_HPP
#define LAUNCH_TEST_PARAM_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "rttypes.h"
#include "cmdlparser.h"

using namespace std;

#define MAX_STP_NAME 100

// DO NOT CHANGE THE ORDER OF THE FOLLOWING ENUM
enum ParamPos {
  startTaskPos,
};

struct TaskParam {
  pid_t id;
  unsigned cpu;
  lt_t e;
  lt_t d;
  lt_t p;
  lt_t ss;			// sum self suspension
  lt_t tDuration;		// testing duration
  TaskParam(pid_t idp, unsigned _cpu, lt_t ep, lt_t dp, lt_t pp, lt_t pss, lt_t _tDuration)
  {id = idp; cpu = _cpu; e = ep; d = dp; p = pp; ss = pss; tDuration = _tDuration;}
};

class TaskSet;

class LaunchTestParam {

private:
  LaunchTestParam();
  LaunchTestParam(const LaunchTestParam&);
  LaunchTestParam& operator=(LaunchTestParam&);
  static LaunchTestParam *launchTestParamInstance;

  FILE *testParamF;
  char testParamFN[MAX_STP_NAME];

  TaskSet *taskSet;

  void setParam(unsigned value, unsigned pos);
  unsigned getParam(unsigned pos);

  void setTaskParam(TaskParam taskParam, unsigned pos);
  int getTaskParam(TaskParam *taskParam, unsigned pos);

  void addAllTasks();
  void getAllTasks();
  
  const char* endLaunchTestParam;
  int endOfLaunchTestParam(const char*);
  void addEndMark();

  unsigned  testing_duration;

public:
  static LaunchTestParam* getInstance();
  void initLaunchTestParam();  
  void resetLocalParams();  

  void setOutputName(const char*);
  char* getOutputName();
  void setTaskSet(TaskSet*);

  vector<TaskParam> taskParams;

  void addTask(TaskParam taskParam);
  void makeLaunchTestParam();
  
  vector<TaskParam> getTaskParams();
  void getLaunchTestParam();

  unsigned getTestingDuration();

  void setParameters(const CmdlParser&);
};

#endif
