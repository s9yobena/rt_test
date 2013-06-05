#include "task.hpp"
#include "binpath.h"


#include <cstdio>
#include <unistd.h>
#include <cstdlib>


Task::Task() {
}

Task::~Task() {
}

pid_t Task::getId() {
  return id;
}

pid_t Task::getWaitReturn() {
	return waitReturn;
}

unsigned Task::getCpu() {
  return parameters.cpu;
}

lt_t Task::getExecCost() {
  return parameters.exec_cost;
}

lt_t Task::getDeadline() {
  // For now, return period
  return getPeriod();
}

lt_t Task::getPeriod() {
  return parameters.period;
}

double Task::getUtilization() {
  return (double)((double)(getExecCost())
		  /(double)(getPeriod()));
}

lt_t Task::getSelfSuspension() {
  return selfSuspension;
}


lt_t Task::getPerJobMaxSelfSusp() {
  return perJobMaxSelfSusp;
}

lt_t Task::getTardiness() {
  // For now, return 0;
  return 0;
}

lt_t Task::getTestingDuration() {
	return testingDuration;
}


void Task::setId(pid_t _taskId) {
  id = _taskId;
}

void Task::setWaitReturn(pid_t _waitReturn) {
	waitReturn = _waitReturn;
}



void Task::setCpu(unsigned _cpu) {
  parameters.cpu = _cpu;
}



void Task::setExecCost(lt_t execCost) {
  parameters.exec_cost = execCost;
}

void Task::setPeriod(lt_t period) {
  parameters.period = period;
}

void  Task::setSelfSuspension(lt_t ss) {
  selfSuspension = ss;
}

void  Task::addSelfSuspension(lt_t ss) {
  selfSuspension += ss;
}

void Task::setPerJobMaxSelfSusp(lt_t _perJobMaxSelfSusp) {
  perJobMaxSelfSusp = _perJobMaxSelfSusp;
}

void Task::setTestingDuration(lt_t _tDuration) {
	testingDuration =  _tDuration;
}

void Task::setParameters(struct rt_task taskParams) {
  parameters = taskParams;
}

void Task::execute(void) {
	pid_t pid, wait_return;
	int wait_status;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	// forked task
	if (pid == 0) {

		printf( "executing time and rtspin " );
		char wcet[20];
		char period[20];
		char duration[20];
		sprintf(wcet,"%d",getExecCost());
		sprintf(period,"%d",getPeriod());
		sprintf(duration,"%d",getTestingDuration());
		
		execl( TIME_PATH, TIME_BIN,
		       "-f",
		       " \"%P\" ",
		       "-o",
		       // "cpuusagefile",
		       TS_CPU_U_F,
		       "-a",
		       RTSPIN_PATH, 
		       "-w",
		       wcet,
		       period,
		       duration,
		       (char *) NULL );

		// char wcet[20];
		// char period[20];
		// char cnt[20];
		// sprintf(wcet,"%d",10);
		// sprintf(period,"%d",100);
		// sprintf(cnt,"%d",1000);


		// execl( "./base_task","base_task",
		//        wcet,
		//        period,
		//        cnt,		       
		//        (char *) NULL );

		perror( "could not execute time or rtspin " );

		exit(EXIT_FAILURE);

	} else { 		// parent
		// Save child pid to wait for.
		setWaitReturn(pid);
	}

}
