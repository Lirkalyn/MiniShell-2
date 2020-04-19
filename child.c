/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** small-desu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i;

    for (i = 0; i < n; i++)
        if (s1[i] != s2[i])
            return ((s1[i] - s2[i]));
    return (0);
}

char **lister(char *str)
{
    int len = 0;
    int nb = 0;
    char **rsl;

    for (int i = 0; str[i] != '\0'; i++)
        nb += (str[i] == ':') ? 1 : 0;
    rsl = (char **)malloc((nb + 2) * sizeof(char *));
    rsl[(nb + 1)] = NULL;
    for (int i = 0; i < (nb + 1); i++) {
        for (len = 0; str[len] != '\0' && str[len] != ':'; len++);
        rsl[i] = (char *)malloc((len + 1) * sizeof(char));
        rsl[i][len] = '\0';
        for (int pos = 0; str[pos] != '\0' && str[pos] != ':'; pos++)
            rsl[i][pos] = str[pos];
        str = (str + len + 1);
    }
    return rsl;
}

int cmd_finder(char **dirs, cmd *cmds, int pos)
{
    DIR *dir;
    struct dirent *dp;
    int len = 0;

    for (; cmds[pos].bin[len] != '\0'; len++);
    len++;
    for (int i = 0; dirs[i] != NULL; i++) {
        dir = opendir(dirs[i]);
        while ((dp = readdir(dir)) != NULL)
            if (my_strncmp(dp->d_name, cmds[pos].bin, len) == 0) {
                closedir(dir);
                return i;
            }
        closedir(dir);
    }
    return -1;
}

/*int forking(cmd cmds, char *envp[], int in , int out)
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
        if ((pid = wait(&status)) < 0) {
            perror("wait");
            exit(1);
        }
    }
    else {
        perror("fork failed");
        exit(2);
    }
}*/

int prefork(char *envp[], char **splitted, char **arg, cmd *cmds) // remove splitted
{
    int pos = 0;
    char *tmp = NULL;
    char **dirs = NULL;
    char *path;

    for (; envp[pos] != NULL && my_strcmp(envp[pos], "PATH=\0") != 0; pos++);
    if (my_strcmp(envp[pos], "PATH=\0") == 0)
        tmp = (envp[pos] + 5);
    dirs = lister(tmp);
    for (int i = 0; i < cmds->nb; i++) {
        pos = cmd_finder(dirs , cmds, i);
        if (pos >= 0)
            cmds[i].path = pathmaker(dirs[pos], cmds[i].bin);
        else
            return not_found(cmds[i]);
        cmds = argv_filler(cmds, i);
        if (cmds == NULL)
            return 84;
    }
    return piping(cmds, envp);
}