/*    rt_test
 *      
 *    Youcef A. Benabbas.
 */

#include "cmdlparser.h"
#include "taskset.hpp"

#include "launchtestparam.hpp"
#include <unistd.h>

#include "testresults.hpp"
// #include "tracingdaemon.hpp"

#include "tasksetgenerator.hpp"	// for generating outliers

int main(int argc, char **argv) {

	TaskSet *taskSet;

	LaunchTestParam *launchTestParam;
	CmdlParser cmdlParser(argc, argv);

	double start_test_t, release_outlier_t, end_test_t;

	taskSet = new TaskSet();
	launchTestParam = LaunchTestParam::getInstance();

	launchTestParam->initLaunchTestParam();
 	launchTestParam->setParameters(cmdlParser);
	launchTestParam->getLaunchTestParam();

	taskSet->updateAllTasks(launchTestParam);



	start_test_t = 0;
	end_test_t = 0;
	release_outlier_t = 0;

	// Start executing all tasks 
	start_test_t = taskSet->releaseAllTasks();
	
	sleep (launchTestParam->getTestingDuration());

	TestResults::add(start_test_t, release_outlier_t);
	cout<<"End of rt_test test"
	    <<endl;
	sleep (5);
	
	cout<<"The effective taskset cpu usage is "
	    <<taskSet->getMeasuredCpuUsagePerCent()
	    <<" %"
	    <<endl;


	return 0;
}

