#include "tasksetgenerator.hpp"
#include "taskset.hpp"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "tasksetparam.hpp"

using namespace std;



TaskSetGenerator::TaskSetGenerator() {
}

TaskSetGenerator* TaskSetGenerator::generateTaskSetInstance = 0;

TaskSetGenerator* TaskSetGenerator::getInstance() {
  
	if (!generateTaskSetInstance) {
		generateTaskSetInstance = new TaskSetGenerator();
	}
	return generateTaskSetInstance;
}

void TaskSetGenerator::setTaskSet(TaskSet *_taskSet) {
	taskSet = _taskSet;
}

void  TaskSetGenerator::generateTaskSet(const char* _generate_param_f) {

	lt_t testD;
	
	pid_t currPid;
	float tmpExecCost;

	unsigned currentU;
	unsigned tmpU;
	unsigned targetU;
	
	unsigned period_l_r;	// milliseconds
	unsigned period_u_r;
	unsigned tmpPeriod;
	
	unsigned utilization_l_r;	// percent
	unsigned utilization_u_r;
	unsigned tmpUtilization;

	TaskSetParam *taskSetParam;
	taskSetParam = TaskSetParam::getInstance();
	taskSetParam->initTaskSetParam(_generate_param_f);
	taskSetParam->getTaskSetParam();
		
	// starting pid (only for testing, not the real pid)
	currPid = 0;

	tmpExecCost = 0.0;
	tmpPeriod = 0.0;
	currentU = 0;

	// testing duration
	testD = taskSetParam->get_test_duration();

	// Target utilization
	targetU = taskSetParam->get_target_utilization();

	// draw task utilization from this range
	utilization_u_r = taskSetParam->get_utilization_u_r();
	utilization_l_r = taskSetParam->get_utilization_l_r();

	// draw period from this range
	period_u_r = taskSetParam->get_period_u_r();
	period_l_r = taskSetParam->get_period_l_r();

	
	// Generate tasks until utilization cap is reached
	do {
		// Draw task period
		// tmpPeriod = 10 + rand()% 90;
		tmpPeriod = period_l_r  
			+ rand() % (period_u_r - period_l_r);

		// Draw task utilitzation
		tmpUtilization = utilization_l_r
			+ rand() %  (utilization_u_r - utilization_l_r);

		// Compute task execution cost
		tmpExecCost = (tmpUtilization * 1E-2) * tmpPeriod;
			
		// Add task with generated parameters 
		taskSet->updateTaskExecCost(tmpExecCost, currPid);
		taskSet->setTaskPeriod(currPid, tmpPeriod);
		
		taskSet->setTaskTestingDuration(currPid, testD);

		currentU += tmpUtilization;
		currPid += 1;
		
	} while (currentU < targetU);
}

