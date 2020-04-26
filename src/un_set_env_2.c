/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** more-desu
*/

#include "../include/minishell_2.h"

int munsetenv(char **envp[], cmd *cmds)
{
    int i = 0;
    int k = 0;
    int pos = -5;
    char **rsl = copy(*envp, 1, &pos);

    if (rsl == NULL || pos == -5 || cmds->args_nb != 1)
        return error_disp(NULL, 3);
    for (; envp[0][k] != NULL; k++)
        free(envp[0][k]);
    free(envp[0][k]);
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