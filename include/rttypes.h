#ifndef RT_TYPES
#define RT_TYPES
#include <stdint.h>
#include "litmus/rt_param.h"	/* for lt_t */
#include "litmus.h"		/* for pid_t */

enum RtTestName {
  RT_TEST=1,
  RT_EFFICACY_TEST,
  RT_EXTRA_CXS,
};

#endif
