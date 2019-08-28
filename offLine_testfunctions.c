// implementations for test functions
// file only works if TESTMODE macro is defined
#include "sparkfun_lte.h"
#include "testconfig.h"

#ifdef TESTMODE
  char putln(char *str)
  {
    printf("%s\n",str);
    return strlen(str);
  }
#endif
