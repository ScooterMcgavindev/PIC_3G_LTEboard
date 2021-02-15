#include "testconfig.h"

#ifdef TESTMODE
// includes for system
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
// includes for testing the sparkfun_lte system
#include "sparkfun_lte.h"

int main()
{
    printf("%s\n","running tests...");
    // start running them tests
    #ifdef POWERONTEST
    powerOn(); 
    // after power on is called the power pin should be an input
    printf("%s\n","power pin is an output");
    assert(TRISA & (0x01 << POWERPIN) == 1);
    #endif
    #ifdef RESETTEST
    hwReset();
    #endif
    #ifdef ATTEST
    printf("%s\n","testing communication commands...");
    printf("%s\n","send an AT command");
    // with at on
    send_command("-test",true);
    // with at off
    send_command("-test",false);
    printf("%s\n","send a command with a responce...");
    #endif
}

#endif
