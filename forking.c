/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** forking, forking everywhere-desu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell_2.h"

void error_wait(void)
{
    perror("wait");
    exit(1);
}

void error_fork(void)
{
    perror("fork failed");
    exit(2);
}

int loop_forking(cmd cmds, char *envp[], int in , int out)
{
    int c_pid = fork();
    int pid;
    int status;

    if (c_pid == 0) {
        if (in != 0) {
            dup2(in, 0);
            close(in);
        }
        else if (out != 1) {
            dup2(out, 1);
            close(out);
        }
        execve(cmds.path, cmds.argv, envp);
    }
    else if (c_pid > 0) {
        if ((pid = wait(&status)) < 0)
            error_wait();}
    else
        error_fork();
}

int last_forking(cmd cmds, char *envp[], int in)
{
    int c_pid = fork();
    int pid;
    int status;

    if (c_pid == 0) {
        if (in != 0)
            dup2(in, 0);
        execve(cmds.path, cmds.argv, envp);
    }
    else if (c_pid > 0) {
        if ((pid = wait(&status)) < 0)
            error_wait();
    }
    else
        error_fork();
}