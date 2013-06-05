#ifndef TASK_HPP
#define TASK_HPP

#include "rttypes.h"

#define TS_CPU_U_F "cpuusagefile"

class Task {

private:
	pid_t id;
	pid_t waitReturn;  	// used to wait for task to finish execution.
	struct rt_task parameters;
	lt_t selfSuspension;
	lt_t perJobMaxSelfSusp;

	lt_t testingDuration;		// duration of task execution for testing

public:
	Task();
	~Task();
	pid_t getId();
	pid_t getWaitReturn();
	unsigned getCpu();
	lt_t getExecCost();
	lt_t getDeadline();
	lt_t getPeriod(); 
	lt_t getSelfSuspension(); 	// This is how long the task suspended, i.e the sum of all self suspensions
	lt_t getPerJobMaxSelfSusp(); 	// This is the maximum time a job suspended.
	double getUtilization();
	lt_t getTardiness();
	lt_t getTestingDuration();

	

	void setId(pid_t);
	void setWaitReturn(pid_t);
	void setCpu(unsigned);
	void setExecCost(lt_t);
	void setPeriod(lt_t);
	void setSelfSuspension(lt_t);
	void addSelfSuspension(lt_t);
	void setPerJobMaxSelfSusp(lt_t);
	void setTestingDuration(lt_t);
	void setParameters(struct rt_task);

	void execute(void);

};

#endif
