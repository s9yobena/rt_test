#include "cmdlparser.h"

CmdlParser::CmdlParser(int argc, char **argv) {


  int c;
  
  while (1)
    {
      static struct option long_options[] =
	{
	  {"rtg", required_argument, NULL, 'g'},
	  {"rt-test", no_argument, NULL, 't'},
	  {"rt-efficacy_test", no_argument, NULL, 'e'},
	  {"rt-extra_cxs", no_argument, NULL, 'x'},
	  {0, 0, 0, 0}
	};
      /* getopt_long stores the option index here. */
      int option_index = 0;
     
      c = getopt_long (argc, argv, "g:tex", long_options, &option_index);
      
      /* Detect the end of the options. */
      if (c == -1)
	break;
      switch (c)
      	{
      	case 'g':
      	  if (optarg) {
      	    strcpy(this->rtConfigTestName, optarg);
	    printf ("rt test config file set to: %s \n ",this->rtConfigTestName);
      	  }
      	  break;

      	case 't':
	    this->rtTestName = RT_TEST;
	    printf("Setting RT_TEST test \n");
	    break;

      	case 'e':
	    this->rtTestName = RT_EFFICACY_TEST;
	    printf("Setting RT_EFFICACY_TEST test \n");
	    break;

      	case 'x':
	    this->rtTestName = RT_EXTRA_CXS;
	    printf("Setting RT_EXTRA_CXS test \n");
	    break;

	  
      	case '?':
      	  /* getopt_long already printed an error message. */
      	  break;

      	default:
      	  break;
      	}
    }
}

CmdlParser::~CmdlParser() {
}

