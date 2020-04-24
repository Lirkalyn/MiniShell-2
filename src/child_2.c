/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** smaller-desu
*/

#include "../include/minishell_2.h"

int exe_checker(char *pathname)
{
    int test = 0;

    if (access(pathname, F_OK) != 0)
        test += 1;
    else {
        if (access(pathname, R_OK) != 0)
            test += 1;
        if (access(pathname, X_OK) != 0)
            test += 1;
    }
    return test;
}

int not_found(cmd cmds)
{
        my_puterror(cmds.bin, 2);
        my_puterror(": Command not found.", 0);
        if (cmds.nb > 1)
            my_puterror("pipe impossible, exit.", 0);
        return 1;
}

cmd *argv_filler(cmd *cmds, int pos)
{
    int nb = (cmds[pos].args_nb + 1);
    int i = 0;

    cmds[pos].argv = malloc((nb + 1) * sizeof(char *));
    if (cmds[pos].argv == NULL)
        return NULL;
    cmds[pos].argv[nb] = NULL;
    cmds[pos].argv[0] = cmds[pos].bin;
    for (; i < cmds[pos].args_nb; i++)
        cmds[pos].argv[(i + 1)] = cmds[pos].args[i];
    return cmds;
}

int piping(cmd *cmds, char *envp[])
{
    int i = 0;
    int in = 0;
    int fd[2];
    cmd last = cmds[(cmds[0].nb - 1)];

    char *line = NULL;
    size_t size;

    for (i = 0; i < cmds[0].nb; i++)
        if (exe_checker(cmds[i].path) != 0)
            return 1;
    for (i = 0; i < (cmds[0].nb - 1); i++) {
        pipe(fd);
        loop_forking(cmds[i], envp, in , fd[1]);
        close(fd[1]);
        in = fd[0];
    }
    return last_forking(last, envp, in);
}