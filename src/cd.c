/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** built-desu
*/

#include "../include/minishell_2.h"

int my_strcmp(char const *s1, char const *s2)
{
    int i;

    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
        if (s1[i] != s2[i])
            return ((s1[i] - s2[i]));
    return (0);
}

int cd_checker(char *pathname)
{
    int test = 0;

    if (access(pathname, F_OK) != 0)
        test += 1;
    else if (access(pathname, X_OK) != 0)
            test += 1;
    return test;
}

char *pathmaker(char *start, char *end)
{
    int len1 = 0;
    int len2 = 0;
    char *rsl;
    int i = 0;
    int j = 0;
    int nb[3] = {[0 ... 2] = 0};

    for (; start[i] != '\0' && nb[1] >= 0; i++)
        nb[0] += (start[i] == '/') ? 1 : 0;
    for (; end[len2] != '\0'; len2 += 1)
        nb[1] += (end[len2] == '.' && end[(len2 + 1)] == '.'
                    && end[(len2 + 1)] == '/') ? 1 : 0;
    for (; start[len1] != '\0' && nb[2] != (nb[0] - nb[1]); len1 += 1)
        nb[2] += (start[(len1 + 1)] == '/') ? 1 : 0;
    rsl = (char *)malloc((len1 + len2 + 2) * sizeof(char));
    rsl[(len1 + len2 + 1)] = '\0';
    for (i = 0; i < len1; rsl[i] = start[i], i++);
    rsl[i++] = '/';
    for (j += (3 * nb[1]); end[j] != '\0'; rsl[i] = end[j], i++, j++);
    return rsl;
}

char *cd2(char *folder, char *envp[])
{
    int pos = 0;
    int len1 = 0;
    int len2 = 0;
    char *tmp = NULL;
    char *rsl = NULL;
    int i = 0;

    for (; envp[pos] != NULL && my_strcmp(envp[pos], "HOME=\0") != 0; pos++);
    if (my_strcmp(envp[pos], "HOME=\0") == 0)
        tmp = (envp[pos] + 5);
    for (; folder[len1] != '\0'; len1 += 1);
    for (; tmp[len2] != '\0'; len2 += 1);
    rsl = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    rsl[(len1 + len2)] = '\0';
    for (; tmp[i] != '\0'; rsl[i] = tmp[i], i++);
    rsl[i++] = '/';
    pos = (folder[1] == '\0') ? 1 : 2;
    for (; folder[pos] != '\0'; rsl[i] = folder[pos++], i++);
    return rsl;
}

int cd(cmd *cmds, char **envp[])
{
    int pos = folder_finder(cmds->args, cmds->args_nb);
    char *tmp = NULL;

    if (pos < 0)
        return cd_go_back(cmds, envp, pos); //
    cmds->path = (cmds->args[pos][0] == '/') ? cmds->args[pos] : NULL;
    if (pos >= 0 && cmds->args_nb != 0 && cmds->args[pos][0] != '/') {
        if (cmds->args[pos][0] == '~')
            cmds->path = cd2(cmds->args[pos], *envp);
        else
            cmds->path = pathmaker(getcwd(NULL, 0), cmds->args[pos]);
        tmp = cmds->args[pos];
        if (cmds->path == NULL)
            return 84;
    }
    if (pos >= 0 && cmds->path != NULL && cd_checker(cmds->path) == 0)
        return change_dir(cmds->path, envp);
    else if (pos >= 0 && cmds->path != NULL && cd_checker(cmds->path) != 0)
        return error_disp(cmds->args[pos], 0);
}