/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** the sequel-desu
*/

#include "../include/minishell_2.h"

int setenv_lenght(cmd *cmds)
{
    int len = 0;
    int men = 0;

    if (cmds->args_nb != 2)
        return -84;
    for (; cmds->args[0][len] != '\0'; len++);
    for (; cmds->args[1][men] != '\0'; men++);
    return (len + men);
}

int msetenv(char **envp[], cmd *cmds)
{
    int i = 0;
    int j = 0;
    int len = setenv_lenght(cmds);
    int pos = -5;
    char **rsl = copy(*envp, 2, &pos);

    if (rsl == NULL || pos == -5 || cmds->args_nb != 2 || len == -84)
        return error_disp(NULL, 2);
    rsl[pos] = (char *)malloc((len + 2) * sizeof(char));
    rsl[pos][(len + 1)] = '\0';
    for (; cmds->args[0][i] != '\0'; rsl[pos][i] = cmds->args[0][i], i++);
    rsl[pos][i++] = '=';
    if (cmds->args[1] != NULL)
        for (; cmds->args[1][j] != '\0'; rsl[pos][i++] = cmds->args[1][j++]);
    *envp = rsl;
}

int munsetenv(char **envp[], cmd *cmds)
{
    int i = 0;
    int pos = -5;
    char **rsl = copy(*envp, 1, &pos);

    if (rsl == NULL || pos == -5 || cmds->args_nb != 1)
        return error_disp(NULL, 3);
    for (; rsl[i] != NULL && my_strcmp(rsl[i], cmds->args[0]) != 0; i++);
    for (int j = i; rsl[j] != NULL; rsl[j] = rsl[(j + 1)], j++);
    *envp = rsl;
    return 0;
}

int menv(char *envp[])
{
    int i = 0;

    for (; envp[i] != NULL; i++)
        myputstr(envp[i], 0);
    return 0;
}

int mexit(void)
{
    myputstr("exit", 0);
    exit(0);
}