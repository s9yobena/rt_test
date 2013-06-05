#ifndef TASK_SET_GENERATOR_HPP
#define TASK_SET_GENERATOR_HPP

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include "cstring"
#include <iostream>

using namespace std;

class TaskSet;




class TaskSetGenerator {

  
private:
	TaskSetGenerator();
	TaskSetGenerator(const TaskSetGenerator&);
	TaskSetGenerator& operator= (const TaskSetGenerator&);
	static TaskSetGenerator* generateTaskSetInstance;

	TaskSet *taskSet;

public:
	static TaskSetGenerator* getInstance();
	void setTaskSet(TaskSet*);
	void generateTaskSet(const char*);
};

#endif
