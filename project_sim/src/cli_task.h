#ifndef _CLI_TASK_H_
#define _CLI_TASK_H_

#include <stdint.h>

#define CLI_MAX_CMD_ARGS            20   // The max number of arguments

/**
 * @brief function pointer type of CLI command handlers.
 *
 * All CLI handlers must follow this prototype.
 *
 * @note    Currently, the return value of CLI handlers are ignored. However,
 *          to keep backward compatiblity, CLI handlers must return 0.
 */
typedef int  (*cli_cmd_handler_t)(int argc, char *argv[]);

/**
* @brief struct cli_command_t - The data structure to describe the cli user commands.
*
*/
typedef struct cli_command {
    const char *cmd;
    const char *cmd_usage;
    cli_cmd_handler_t cmd_handle;
    struct cli_command *sub;       /**< Sub-commands. */
}cli_command_t;

/**
 * @brief The CLI control block definition.
 *
 */
typedef struct cli_cb {
    uint8_t         state;                  /**< Defines the init status. */
    cli_command_t   *cmd;                   /**< A pointer to the CLI commands. */
    char            *tok[CLI_MAX_CMD_ARGS]; /**< The tokenized input command. */
}cli_cb_t;

int createCliTask(void);

#endif /* _CLI_TASK_H_ */

