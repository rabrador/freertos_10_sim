#include <stdio.h>
#include <stdlib.h>

#include "cli_task.h"
#include "cmd_parser.h"

#include "FreeRTOS.h"
#include "task.h"

int main(void)
{
    createCliTask();
    createCmdParserTask();

    vTaskStartScheduler();
    return 0;
}

/********************************************************/
/* This is a stub function for FreeRTOS_Kernel */
void vMainQueueSendPassed( void )
{
    return;
}

/* This is a stub function for FreeRTOS_Kernel */
void vApplicationIdleHook( void )
{
    return;
}

