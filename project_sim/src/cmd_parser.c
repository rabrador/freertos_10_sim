#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli_task.h"
#include "cli_sys.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

QueueHandle_t xCmdParserQueue = NULL;

static int sys_cmd_part(int argc, char *argv[])
{
    cli_sys_handler(argc, argv);
    return 0;
}

static cli_command_t cmd_group_table[] = {
    { "sys",       "system gorup",         sys_cmd_part,          NULL },
    { NULL, NULL, NULL, NULL},
};

static int cli_parser_handler(int argc, char *argv[])
{
    cli_command_t *p_table = NULL;
    
    if (argc <= 1)
        return 0;

    for (p_table=&cmd_group_table[0]; p_table->cmd; p_table++) {
        if (!strcmp(argv[0], p_table->cmd)) {
            if (p_table->cmd_handle) {
                p_table->cmd_handle(argc-1, &argv[1]);
            }
        }
    }
    return 0;
}

static int CmdParserToArgu(int *argc, char **argv, char *pbuf)
{
    int count = 0;
    char *p = strtok(pbuf, " ");
    
    argv[count] = p;
    count++;
    
    while ((p = strtok(NULL, " ")) != NULL) {
        argv[count] = p;
        count++;
    }
    
    *argc = count;
    return 0;
}

static void cmdParserTask(void *pvParameters)
{
    char *pBuf = NULL;
    int argc = 0;
    char *argv[10] = {0};

    while(1) {
        if (xQueueReceive(xCmdParserQueue, (void *)&pBuf, portMAX_DELAY) == pdTRUE){
            CmdParserToArgu(&argc, &argv[0], pBuf);
            cli_parser_handler(argc, argv);
        }
        free(pBuf);
    }
}

int createCmdParserTask(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;


    xCmdParserQueue = xQueueCreate( 10, sizeof( unsigned long ) );
    if (xCmdParserQueue == NULL) {
        printf("create cmd parser queue failed! \n");
        return -1;
    }

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    cmdParserTask,         /* Function that implements the task. */
                    "cmd_parser_task",          /* Text name for the task. */
                    512,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY + 5,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */

    if( xReturned != pdPASS )
    {
        printf("create cmd parser task failed.\n");
        return -1;
    }

    return 0;
}

