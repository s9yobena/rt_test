/*    rt_config-test -- real-time configuration for running tests
 *      
 *    Youcef A. Benabbas
 */

#include "cmdlparser.h"
#include "launchtestparam.hpp"
#include "taskset.hpp"
#include "launchtest.hpp"
#include "tasksetgenerator.hpp"


int main(int argc, char **argv) {


        CmdlParser cmdlParser(argc, argv);    
	
	TaskSet *taskSet;
	taskSet = new TaskSet();
	LaunchTestParam *launchTestParam;
	LaunchTest *launchTest;
	TaskSetGenerator *generateTaskSet;

	launchTestParam = LaunchTestParam::getInstance();
	launchTest = LaunchTest::getInstance();
	launchTest->setParameters(cmdlParser);
	generateTaskSet = TaskSetGenerator::getInstance();

	launchTestParam->initLaunchTestParam();
	launchTestParam->setOutputName("rttestconfigfile.rtg");
	launchTestParam->setTaskSet(taskSet);

	
	// Generate a taskset.
	generateTaskSet->setTaskSet(taskSet);
	generateTaskSet->generateTaskSet("tasksetconfigfile");
	
	// Write the generated taskset to file.
	launchTestParam->makeLaunchTestParam();

	// Launch test.
	launchTest->callLaunchTest(launchTestParam->getOutputName());

	return 0;
}
