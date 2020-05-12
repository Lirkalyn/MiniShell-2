/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** small-desu
*/

#include "../include/minishell_2.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i;

    for (i = 0; i < n; i++)
        if (s1[i] != s2[i])
            return ((s1[i] - s2[i]));
    return (0);
}

char **spe_patch(char **dirs, char *envp[])
{
    int i = 0;
    int where = -1;
    char *tmp = NULL;

    for (; envp[i] != NULL; i++)
        where = (my_strcmp(envp[i], "HOME=\0") == 0) ? i : where;
    if (where == -1)
        return NULL;
    tmp = (envp[where] + 5);
    for (i = 0; dirs[i] != NULL; i++)
        if (dirs[i][0] == '~' && dirs[i][1] == '/')
            dirs[i] = pathmaker(tmp, (dirs[i] + 2));
        else if (dirs[i][0] == '~' && dirs[i][1] != '/')
            dirs[i] = pathmaker(tmp, (dirs[i] + 1));
    return dirs;
}

char **lister(char *str, char *envp[])
{
    int len = 0;
    int nb = 0;
    char **rsl;

    for (int i = 0; str[i] != '\0'; i++)
        nb += (str[i] == ':') ? 1 : 0;
    rsl = (char **)malloc((nb + 2) * sizeof(char *));
    if (rsl == NULL)
        return NULL;
    rsl[(nb + 1)] = NULL;
    for (int i = 0; i < (nb + 1); i++) {
        for (len = 0; str[len] != '\0' && str[len] != ':'; len++);
        rsl[i] = (char *)malloc((len + 1) * sizeof(char));
        rsl[i][len] = '\0';
        for (int pos = 0; str[pos] != '\0' && str[pos] != ':'; pos++)
            rsl[i][pos] = str[pos];
        str = (str + len + 1);
    }
    return spe_patch(rsl, envp);
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

int prefork(char *envp[], cmd *cmds)
{
    int pos = 0;
    char *tmp = NULL;
    char **dirs = NULL;

    for (; envp[pos] != NULL && my_strcmp(envp[pos], "PATH=\0") != 0; pos++);
    if (my_strcmp(envp[pos], "PATH=\0") == 0)
        tmp = (envp[pos] + 5);
    dirs = lister(tmp, envp);
    for (int i = 0; i < cmds->nb; i++) {
        pos = cmd_finder(dirs , cmds, i);
        if (pos >= 0)
            cmds[i].path = pathmaker(dirs[pos], cmds[i].bin);
        else if (cmds[i].bin[0] == '/' && exe_checker(cmds[i].bin) == 0)
            cmds[i].path = cmds[i].bin;
        else
            return not_found(cmds[i]);
        cmds = argv_filler(cmds, i);
        if (cmds == NULL)
            return 84;}
    return piping(cmds, envp);
}