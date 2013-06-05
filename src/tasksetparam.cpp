#include "tasksetparam.hpp"
#include <stdio.h>

TaskSetParam::TaskSetParam() {
}

TaskSetParam* TaskSetParam::taskSetParamInstance = 0;

TaskSetParam* TaskSetParam::getInstance() {
  if (!taskSetParamInstance) {
    taskSetParamInstance = new TaskSetParam();
  }
  return taskSetParamInstance;
}

void TaskSetParam::initTaskSetParam(const char *tasksetconfigfile) {
  endTaskSetParam = "End";
  resetLocalParams();
  strcpy(task_set_param_f_n, tasksetconfigfile);
}

void TaskSetParam::resetLocalParams() {
  test_duration = 0;
  utilization_u_r = 0;
  utilization_l_r = 0;
  period_u_r = 0;
  period_l_r = 0;
}

int TaskSetParam::endOfTaskSetParam(const char *line) {
  if(!strcmp(line,endTaskSetParam))
    return 1;
  else
    return 0;
}

void TaskSetParam::setParam(unsigned value, unsigned pos) {
  rewind(task_set_param_f);
  char line[100];
  char buf[100];
  unsigned currLineNbr;
  currLineNbr = 0;
  do {
    if (currLineNbr == pos) {
      sprintf(buf, "%d\n", value);
      fputs (buf, task_set_param_f);
      break;
    }
    currLineNbr++;
  } while (fgets (line, sizeof line, task_set_param_f) != NULL);
}

unsigned TaskSetParam::getParam(unsigned pos) {
  rewind(task_set_param_f);
  char line[100];
  unsigned currLineNbr;
  unsigned ret;
 
  currLineNbr = 0;
  while (fgets (line, sizeof line, task_set_param_f) != NULL) {
    if (currLineNbr == pos) {
      sscanf(line,"%u",&ret);
      return ret;
    }
    currLineNbr++;
  }
}

void TaskSetParam::addEndMark() {

  task_set_param_f = fopen(task_set_param_f_n,"a");
  fputs(endTaskSetParam,task_set_param_f);
  fclose(task_set_param_f); 
}

// Do not modify this function unless you know 
// very well what you are doing
void TaskSetParam::makeTaskSetParam() {
  task_set_param_f = fopen(task_set_param_f_n,"w+");
  // DO NOT CHANGE THE ORDER OF THE FOLLOWING BLOCK
  // START
  setParam(test_duration, test_duration_pos);
  setParam(target_utilization, target_utilization_pos);
  setParam(utilization_u_r, utilization_u_r_pos);
  setParam(utilization_l_r, utilization_l_r_pos);
  setParam(period_u_r, period_u_r_pos);
  setParam(period_l_r, period_l_r_pos);
  // END
  fclose(task_set_param_f); 
  addEndMark();
}

void TaskSetParam::getTaskSetParam() {
	task_set_param_f = fopen(task_set_param_f_n,"r+");
	if (task_set_param_f==NULL){
		perror("could not open launchtestparam file:");
		printf("%s\n",task_set_param_f_n);
		exit(EXIT_FAILURE);
	}
	// DO NOT CHANGE THE ORDER OF THE FOLLOWING BLOCK
	// START
	test_duration      = getParam(test_duration_pos);
	target_utilization = getParam(target_utilization_pos);
	utilization_u_r    = getParam(utilization_u_r_pos);
	utilization_l_r    = getParam(utilization_l_r_pos);
	period_u_r         = getParam(period_u_r_pos);
	period_l_r         = getParam(period_l_r_pos);
	// END  

	fclose(task_set_param_f); 
}

unsigned TaskSetParam::get_test_duration() {
	return test_duration;
}

unsigned TaskSetParam::get_utilization_u_r() {
	return utilization_u_r;
}

unsigned TaskSetParam::get_utilization_l_r() {
	return utilization_l_r;
}

unsigned TaskSetParam::get_period_u_r() {
	return period_u_r;
}

unsigned TaskSetParam::get_period_l_r() {
	return period_l_r;
}

unsigned TaskSetParam::get_target_utilization() {
	return target_utilization;
}
