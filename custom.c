/**
 * 2026
 * Avery Allison
 * custom dwm functionality
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "custom.h"

#define BACKGROUND_EXTRA_CHARS  2

static pid_t autostart_pgid = 0;

/*
 * run the script `filename` in the background on `DWM_AUTOSTART_INTERPRETER`.
 * return: the pid of the interpreter, or `errno` if forking fails.
 */
static pid_t run_background_script(char *filename);

/*
 * run the script `filename` on `DWM_AUTOSTART_INTERPRETER`.
 * return: the pid of the interpreter, or `errno` if forking fails.
 */
static pid_t run_script(char *filename);

void
autostart(void)
{
    autostart_pgid = run_script(DWM_AUTOSTART);
    run_background_script(DWM_AUTOSTART_BACKGROUND);
}

static pid_t
run_background_script(char *filename)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "%s: ", filename);
        perror("unable to create a child process to run this script");
        return (pid_t) errno;
    }

    if (pid == 0)
    {
        if (setpgid(0, autostart_pgid) != 0)
        {
            perror("unable to add process to group");
            exit(errno);
        }

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
    return pid;
}

static pid_t
run_script(char *filename)
{
    int pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "%s: ", filename);
        perror("unable to create a child process to run this script");
        return (pid_t) errno;
    }

    if (pid == 0)
    {
        if (setpgid(0, 0) != 0)
        {
            perror("unable to add process to group");
            exit(errno);
        }

        execlp(DWM_AUTOSTART_INTERPRETER,
            DWM_AUTOSTART_INTERPRETER, "-c", filename, (char *) NULL);
        perror("unable to launch shell interpreter");
        exit(errno);
    }

    wait(NULL);
    return pid;
}

int
terminate_autostart(void)
{
    if (autostart_pgid == 0)
    {
        fprintf(stderr, "no autostart group found\n");
        return -1;
    }

    if (kill(-autostart_pgid, SIGTERM) != 0)
    {
        perror("unable to kill autostart group");
        return -2;
    }

    return 0;
}
