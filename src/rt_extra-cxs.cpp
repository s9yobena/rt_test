/*    rt_extra-cxs
 *      
 *    Youcef A. Benabbas.
 */

#include <iostream>
#include <unistd.h>

#include "cmdlparser.h"
#include "taskset.hpp"
#include "launchtestparam.hpp"
#include "testresults.hpp"

using namespace std;

int main(int argc, char **argv) {

	TaskSet *taskSet;

	LaunchTestParam *launchTestParam;
	CmdlParser cmdlParser(argc, argv);

	double start_test_t, cxs_outlier_t, end_test_t;

	taskSet = new TaskSet();
	launchTestParam = LaunchTestParam::getInstance();

	launchTestParam->initLaunchTestParam();
 	launchTestParam->setParameters(cmdlParser);
	launchTestParam->getLaunchTestParam();

	taskSet->updateAllTasks(launchTestParam);



	start_test_t = 0;
	end_test_t = 0;
	cxs_outlier_t = 0;

	// Start executing all tasks 
	start_test_t = taskSet->releaseAllTasks();

	// Compute when to insert the outlier:
	unsigned insert_outlier_t;
	insert_outlier_t =3*(launchTestParam->getTestingDuration()/4);
	sleep(insert_outlier_t);

	// Release outlier
	cxs_outlier_t = wctime();

	pid_t pid;
	pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
    
	if (pid == 0) {
		printf("executing setextracxs\n");
		execl( "./../liblitmus/setextracxs","setextracxs",
		       "-x","1",
		       "-c","4",
		       "-i","85000000",
		       "-s","0",		       
		       (char *) NULL );
		perror( "could not execute execl(setextracxs)" );
		exit(EXIT_FAILURE);
	    
	} else {

		TestResults::add(start_test_t, cxs_outlier_t);
		cout<<"End of rt_extra-cxs"
		    <<endl;

		return 0;

	}
}
