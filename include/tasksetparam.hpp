#ifndef TASK_SET_PARAM_HPP
#define TASK_SET_PARAM_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "rttypes.h"
#include "cmdlparser.h"

using namespace std;



// DO NOT CHANGE THE ORDER OF THE FOLLOWING ENUM

class TaskSetParam {

enum ParamPos {
	comment_1,
	test_duration_pos,
	comment_2,
	target_utilization_pos,
	comment_3,
	utilization_u_r_pos,
	comment_4,
	utilization_l_r_pos,
	comment_5,
	period_u_r_pos,
	comment_6,
	period_l_r_pos
};


private:
	
	unsigned test_duration;
	unsigned target_utilization;
	unsigned utilization_u_r;
	unsigned utilization_l_r;
	unsigned period_u_r;
	unsigned period_l_r;
		
	TaskSetParam();
	TaskSetParam(const TaskSetParam&);
	TaskSetParam& operator=(TaskSetParam&);
	static TaskSetParam *taskSetParamInstance;

	FILE *task_set_param_f;
        char task_set_param_f_n[100]; 

	void setParam(unsigned value, unsigned pos);
	unsigned getParam(unsigned pos);

	const char* endTaskSetParam;
	int endOfTaskSetParam(const char*);
	void addEndMark();

public:
	static TaskSetParam* getInstance();
	void initTaskSetParam(const char*);  
	void resetLocalParams();  

	void makeTaskSetParam();
	void getTaskSetParam();

	unsigned get_test_duration();
	unsigned get_utilization_u_r();
	unsigned get_utilization_l_r();
	unsigned get_period_u_r();
	unsigned get_period_l_r();
	unsigned get_target_utilization();
	

};

#endif
