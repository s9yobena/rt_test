/*    rt_global-test
 *      
 *    Youcef A. Benabbas.
 */

#include "cmdlparser.h"
#include "taskset.hpp"

#include "launchtestparam.hpp"
#include <unistd.h>

#include "testresults.hpp"

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



	TaskSet *outlier;
	TaskSetGenerator *outlierGenerator;
	outlier = new TaskSet();
	outlierGenerator = TaskSetGenerator::getInstance();;
	outlierGenerator->setTaskSet(outlier);
	outlierGenerator->generateTaskSet("outlierconfigfile");
	
	start_test_t = 0;
	end_test_t = 0;
	release_outlier_t = 0;

	// Start executing all tasks 
	start_test_t = taskSet->releaseAllTasks();

	// Compute when to insert the outlier:
	unsigned insert_outlier_t;
	insert_outlier_t =2*(launchTestParam->getTestingDuration()/3);
	sleep(insert_outlier_t);

	// Release outlier
	release_outlier_t = outlier->releaseAllTasks();
	
	TestResults::add(start_test_t, release_outlier_t);
	cout<<"End of rt_efficacy test"
	    <<endl;

	return 0;
}
