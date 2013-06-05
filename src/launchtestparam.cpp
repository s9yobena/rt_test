#include "launchtestparam.hpp"
#include "taskset.hpp"
#include <stdio.h>

LaunchTestParam::LaunchTestParam() {
}

LaunchTestParam* LaunchTestParam::launchTestParamInstance = 0;

LaunchTestParam* LaunchTestParam::getInstance() {
  if (!launchTestParamInstance) {
    launchTestParamInstance = new LaunchTestParam();
  }
  return launchTestParamInstance;
}

void LaunchTestParam::setOutputName(const char* _rtConfigTestName) {
	strcpy(this->testParamFN, _rtConfigTestName);
}

char* LaunchTestParam::getOutputName() {
  return testParamFN;
}

void LaunchTestParam::setTaskSet(TaskSet *_taskSet) {
  taskSet = _taskSet;
}

void LaunchTestParam::initLaunchTestParam() {
  endLaunchTestParam = "End";
  resetLocalParams();
  this->testing_duration = 0;
}

void LaunchTestParam::resetLocalParams() {
  taskParams.clear();
}
vector<TaskParam> LaunchTestParam::getTaskParams() {
  return taskParams;
}

void LaunchTestParam::addTask(TaskParam taskParam) {
  taskParams.push_back(taskParam);
}

void LaunchTestParam::addAllTasks() {
  unsigned taskParamPos = startTaskPos;
  for (int i=0; i<taskSet->getNbrTasks(); i++) {

    pid_t taskId;
    taskId = taskSet->getTaskId(i);

    setTaskParam(TaskParam(taskId,
			   taskSet->getTaskCpu(taskId),
			   taskSet->getTaskExecCost(taskId),
			   0,
			   taskSet->getTaskPeriod(taskId),
			   taskSet->getTaskSelfSuspension(taskId),
			   taskSet->getTaskTestingDuration(taskId)),
		 taskParamPos);
    taskParamPos++;
  }
}


void LaunchTestParam::getAllTasks() {
  vector<TaskParam>::iterator it;
  unsigned taskParamPos = startTaskPos;
  TaskParam taskParam(0,0,0,0,0,0,0);
  int i=0;
  while(!getTaskParam(&taskParam,startTaskPos+i)) {
    taskParams.push_back(taskParam);
    i++;

    if (taskParam.tDuration > this->testing_duration) {
      this->testing_duration = taskParam.tDuration;
    }
  }
}

int LaunchTestParam::endOfLaunchTestParam(const char *line) {
  if(!strcmp(line,endLaunchTestParam))
    return 1;
  else
    return 0;
}

void LaunchTestParam::setTaskParam(TaskParam taskParam, unsigned pos) {
  rewind(testParamF);
  char line[100];
  char buf[100];
  unsigned currLineNbr;
  currLineNbr = 0;
  do {
    if (currLineNbr == pos) {
      sprintf(buf, "%u %u %llu %llu %llu %llu %llu \n", 
	      taskParam.id, taskParam.cpu, taskParam.e, taskParam.d, taskParam.p, 
	      taskParam.ss, taskParam.tDuration);
      fputs (buf, testParamF);
      break;
    }
    currLineNbr++;
  } while (fgets (line, sizeof line, testParamF) != NULL);
}

int LaunchTestParam::getTaskParam(TaskParam *taskParam, unsigned pos) {
  rewind(testParamF);
  char line[100];
  unsigned currLineNbr;
 
  currLineNbr = 0;
  while (fgets (line, sizeof line, testParamF) != NULL) {
    if (currLineNbr == pos) {
      // check if we reached the end of file
      if (endOfLaunchTestParam(line)) {
      	return 1;
      }
      sscanf(line,"%u %u %u %u %u %u %u",
	     &taskParam->id, &taskParam->cpu, &taskParam->e, &taskParam->d, &taskParam->p, 
	     &taskParam->ss, &taskParam->tDuration);
      return 0;
    }
    currLineNbr++;
  }
  // we should not reach here
  printf("Error parsing file; Correct input file format? \n");
}


void LaunchTestParam::setParam(unsigned value, unsigned pos) {
  rewind(testParamF);
  char line[100];
  char buf[100];
  unsigned currLineNbr;
  currLineNbr = 0;
  do {
    if (currLineNbr == pos) {
      sprintf(buf, "%d\n", value);
      fputs (buf, testParamF);
      break;
    }
    currLineNbr++;
  } while (fgets (line, sizeof line, testParamF) != NULL);
}

unsigned LaunchTestParam::getParam(unsigned pos) {
  rewind(testParamF);
  char line[100];
  unsigned currLineNbr;
  unsigned ret;
 
  currLineNbr = 0;
  while (fgets (line, sizeof line, testParamF) != NULL) {
    if (currLineNbr == pos) {
      sscanf(line,"%u",&ret);
      return ret;
    }
    currLineNbr++;
  }
}

void LaunchTestParam::addEndMark() {

  testParamF = fopen(testParamFN,"a");
  fputs(endLaunchTestParam,testParamF);
  fclose(testParamF); 
}

// Do not modify this function unless you know 
// very well what you are doing
void LaunchTestParam::makeLaunchTestParam() {
  testParamF = fopen(testParamFN,"w+");
  // DO NOT CHANGE THE ORDER OF THE FOLLOWING BLOCK
  // START

  // setParam(mhzCpuClock, cpuClockPos);
  // setCacheTopParam(cacheTopPos);
  // setParam(cxs, cxsPos);
  // setParam(sched, schedPos);
  // setParam(sched2, sched2Pos);
  // setParam(release, releasePos);
  // setParam(send_resched, send_reschedPos);
  // setParam(release_latency, release_latencyPos);
  // setParam(tick, tickPos);
  addAllTasks();  
  // END
  fclose(testParamF); 
  addEndMark();
}

void LaunchTestParam::getLaunchTestParam() {
	// printf("Trying to opne the following rt test config file  %s \n", rtConfigTestName);
	testParamF = fopen(testParamFN,"r+");

	// launchTestPramFile = fopen ("rttestconfigfile.rtg","r+");

	if (testParamF==NULL){
		perror("could not open launchtestparam file");
		exit(EXIT_FAILURE);
	}


	// FILE *f;
	// f = fopen ("rttestconfigfile.rtg","r+");
	// if (f==NULL) {
	// 	perror("Could not open rttestconfigfile.rtg");
	// 	exit(EXIT_FAILURE);
	// }

	// DO NOT CHANGE THE ORDER OF THE FOLLOWING BLOCK
	// START

	// mhzCpuClock = getParam(cpuClockPos);
	// cache_top = getCacheTopParam(cacheTopPos);
	// cxs = getParam(cxsPos);
	// sched = getParam(schedPos);
	// sched2 = getParam(sched2Pos);
	// release = getParam(releasePos);
	// send_resched = getParam(send_reschedPos);
	// release_latency = getParam(release_latencyPos);
	// tick = getParam(tickPos);
	getAllTasks();
	// END  
	fclose(testParamF); 
	// fclose (f);
}

unsigned LaunchTestParam::getTestingDuration() {

  return this->testing_duration;
}

void LaunchTestParam::setParameters(const CmdlParser& cmdlParser) {
  
  strcpy(testParamFN, cmdlParser.rtConfigTestName);
}
