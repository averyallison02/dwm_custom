#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "custom.h"

#define BACKGROUND_EXTRA_CHARS  2

/*
 * run the script `filename` in the background on `DWM_AUTOSTART_INTERPRETER`
 */
static void run_background_script(char *filename);

/*
 * run the script `filename` on `DWM_AUTOSTART_INTERPRETER`.
 */
static void run_script(char *filename);

void
autostart(void)
{
    run_script(DWM_AUTOSTART);
    run_background_script(DWM_AUTOSTART_BACKGROUND);
}

static void
run_background_script(char *filename)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "%s: ", filename);
        perror("unable to create a child process to run this script");
        return;
    }

    if (pid == 0)
    {
        size_t len_command_string = strlen(filename) + BACKGROUND_EXTRA_CHARS;
        char command_string[len_command_string+1];
        if (snprintf(command_string, len_command_string+1, "%s &", filename) != len_command_string)
        {
            perror("unable to create command buffer");
            exit(errno);
        }
        execlp(DWM_AUTOSTART_INTERPRETER,
            DWM_AUTOSTART_INTERPRETER, "-c", command_string, (char *) NULL);
        perror("unable to launch shell interpreter");
        exit(errno);
    }
    wait(NULL);
}

static void
run_script(char *filename)
{
    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "%s: ", filename);
        perror("unable to create a child process to run this script");
        return;
    }

    if (pid == 0)
    {
        execlp(DWM_AUTOSTART_INTERPRETER,
            DWM_AUTOSTART_INTERPRETER, "-c", filename, (char *) NULL);
        perror("unable to launch shell interpreter");
        exit(errno);
    }
    wait(NULL);
}
