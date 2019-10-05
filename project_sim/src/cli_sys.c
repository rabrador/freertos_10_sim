#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli_task.h"
#include "FreeRTOS.h"
#include "task.h"

static int task_system_state(int argc, char *argv[])
{
    char buf[512];
    vTaskList(buf);
//    vTaskGetRunTimeStats(buf);
    printf("\n%s\n", buf);
    return 0;
}

static cli_command_t cli_sys_table[] = {
    { "task",       "show task system state",         task_system_state,          NULL },
    { NULL, NULL, NULL, NULL},
};

int cli_sys_handler(int argc, char *argv[])
{
     cli_command_t *p_table = NULL;

    for (p_table=&cli_sys_table[0]; p_table->cmd; p_table++) {
        if (!strcmp(argv[0], p_table->cmd)) {
            if (p_table->cmd_handle) {
                p_table->cmd_handle(argc-1, &argv[1]);
            }
        }
    }

     return 0;
}
