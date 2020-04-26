/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** to set or not to set-desu
*/

#include "../include/minishell_2.h"

int setenv_lenght(cmd *cmds)
{
    int len = 0;
    int men = 0;

    if (cmds->args_nb >= 1)
        for (; cmds->args[0][len] != '\0'; len++);
    if (cmds->args_nb >= 2)
        for (; cmds->args[1][men] != '\0'; men++);
    return (len + men);
}

int msetenv(char **envp[], cmd *cmds)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int len = setenv_lenght(cmds);
    int pos = -5;
    char **rsl = copy(*envp, 2, &pos);

    if (rsl == NULL || pos == -5 || len == 0)
        return error_disp(NULL, 2);
    for (; envp[0][k] != NULL; k++)
        free(envp[0][k]);
    rsl[pos] = (char *)malloc((len + 2) * sizeof(char));
    if (rsl[pos] == NULL)
        return 84;
    rsl[pos][(len + 1)] = '\0';
    for (; cmds->args[0][i] != '\0'; rsl[pos][i] = cmds->args[0][i], i++);
    rsl[pos][i++] = '=';
    if (cmds->args_nb >= 2)
        for (; cmds->args[1][j] != '\0'; rsl[pos][i++] = cmds->args[1][j++]);
    *envp = rsl;
}

static int where_is(char **envp[], char *str)
{
    int i = 0;

    for (; envp[0][i] != NULL; i++)
        if (my_strcmp(envp[0][i], str) == 0)
            return i;
    return -1;
}

int pre_msetenv(char **envp[], cmd *cmds)
{
    int i = 0;
    int j = 0;
    int where = -1;
    int len = setenv_lenght(cmds);
    char *tmp = NULL;

    if (cmds->args_nb <= 0 || cmds->args_nb > 2)
        return error_disp(NULL, 2);
    where = where_is(envp, cmds->args[0]);
    if (where == -1)
        return msetenv(envp, cmds);
    tmp = malloc((len + 2) * sizeof(char));
    if (tmp == NULL)
        return 84;
    tmp[len + 1] = '\0';
    for (i = 0; cmds->args[0][i] != '\0'; tmp[i] = cmds->args[0][i], i++);
    tmp[i++] = '=';
    if (cmds->args_nb >= 2)
        for (; cmds->args[1][j] != '\0'; tmp[i++] = cmds->args[1][j++]);
    envp[0][where] = tmp;
}