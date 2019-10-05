#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#define CLI_MAX_BUFFER_SIZE         160   // CLI Buffer size (char)
#define CLI_PROMPT ">"

TimerHandle_t xTimer = NULL;

extern QueueHandle_t xCmdParserQueue;

/**
 * Static Global variables for CLI status:
 */
static char cmd_line[CLI_MAX_BUFFER_SIZE + 1]; // Extra space for terminating '\0'
static char cmd_back[CLI_MAX_BUFFER_SIZE + 1]; // Extra space for terminating '\0'

//static cli_cb_t *clicb_ptr;
static uint8_t cmd_line_len = 0;
static uint8_t cursor_pos = 0;

//extern QueueHandle_t xCliQueue;

static void ProcessCharBackspace(void)
{
    if (cursor_pos == 0) {
        return;
    }

    for (uint8_t i = cursor_pos; i < cmd_line_len; i++) {
        cmd_line[i - 1] = cmd_line[i];
    }

    printf("%c",0x08);
    printf("%c",0x20);
    printf("%c",0x08);

    cursor_pos--;
    cmd_line_len--;
}

static void ProcessCharInsert(char ch)
{
    if (cmd_line_len >= CLI_MAX_BUFFER_SIZE) {
        return;
    }

    for (uint8_t i = cursor_pos; i < cmd_line_len; i++) {
        cmd_line[i + 1] = cmd_line[i];
    }

    cmd_line[cursor_pos] = ch;
    cursor_pos++;
    cmd_line_len++;
    printf("%c", ch); //input echo
}

static void ProcessCharPressed(void)
{
    char *pCmdBuf = NULL;
    
    cmd_line[cmd_line_len] = '\0';
    memcpy(cmd_back, cmd_line, (CLI_MAX_BUFFER_SIZE + 1));
    
    pCmdBuf = malloc((CLI_MAX_BUFFER_SIZE + 1));
    if (pCmdBuf == NULL) {
        printf("ProcessCharPressed failed. \n");
    }
    
    memset(pCmdBuf, 0, (CLI_MAX_BUFFER_SIZE + 1));
    
    if (xCmdParserQueue == NULL) {
        free(pCmdBuf);
    }
    else {
        memcpy(pCmdBuf, cmd_line, (CLI_MAX_BUFFER_SIZE + 1));
        xQueueSend(xCmdParserQueue, (void *)&pCmdBuf, 0);
    }
    
    cmd_line_len = 0;
    cursor_pos = 0;
}

static void ProcessCmdData(void)
{
    char ch;

    while (ch = getchar()) {
        switch(ch) {
            case 0x00: // Special Key, read again for real data
                break;
            case 0x08: // Backspace
            case 0x7F:
                ProcessCharBackspace();
                break;
            case 0x0A: // Enter
                ProcessCharPressed();
                printf("\n%s", CLI_PROMPT);
                break;
            case 0xffffffff: // dummy
                break;
            default: // other characters
                ProcessCharInsert(ch);
                break;
        }
    }
}

static void cliTask(void *pvParameters)
{
    for (;;) {
        ProcessCmdData();
        vTaskDelay(10);
    }
}

static void vTimerCallback( TimerHandle_t xTimer )
{
    printf("time out\n");
}

int createCliTask(void)
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    xTimer = xTimerCreate("timer", 1000, pdTRUE, 0, vTimerCallback);
    if (xTimer == NULL) {
        printf("create timer failed. \n");
        return -1;
    }

    xTimerStart(xTimer, 0);

    /* Create the task, storing the handle. */
    xReturned = xTaskCreate(
                    cliTask,         /* Function that implements the task. */
                    "cli_task",          /* Text name for the task. */
                    256,             /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY + 5,/* Priority at which the task is created. */
                    &xHandle );      /* Used to pass out the created task's handle. */

    if( xReturned != pdPASS )
    {
        printf("create cli task failed.\n");
        return -1;
    }

    return 0;
}
