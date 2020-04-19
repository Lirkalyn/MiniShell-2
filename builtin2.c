/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** the sequel-desu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

int msetenv(char **splitted, char **envp[], char **arg)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int len1 = 0;
    int len2 = 0;
    int pos = -5;
    char **rsl = copy(*envp, 2, &pos);

    if (rsl == NULL || pos == -5 || arg == NULL)
        return 84;
    for (; arg[i] != NULL && my_strcmp(arg[i], splitted[2]) != 0; i++);
    for (; splitted[2][len1] != '\0'; len1 += 1);
    for (; arg[(i + 1)] != NULL && arg[(i + 1)][len2] != '\0'; len2 += 1);
    rsl[pos] = (char *)malloc((len1 + len2 + 2) * sizeof(char));
    rsl[pos][(len1 + len2 + 1)] = '\0';
    for (; splitted[2][j] != '\0'; rsl[pos][j] = splitted[2][j], j++);
    rsl[pos][j++] = '=';
    if (arg[(i + 1)] != NULL)
        for (; arg[(i + 1)][k] != '\0'; rsl[pos][j++] = arg[(i + 1)][k++]);
    *envp = rsl;
}

int munsetenv(char **splitted, char **envp[])
{
    int i = 0;
    int pos = -5;
    char **rsl = copy(*envp, 1, &pos);

    if (rsl == NULL || pos == -5)
        return 84;
    for (; rsl[i] != NULL && my_strcmp(rsl[i], splitted[2]) != 0; i++);
    for (int j = i; rsl[j] != NULL; rsl[i] = rsl[(i + 1)], j++);
    *envp = rsl;
    return 0;
}

int menv(char **splitted, char *envp[])
{

    for (int ok = 0; envp[ok] != NULL; ok++)
        myputstr(envp[ok], 0);
    return 0;
}

int mexit(char **splitted, char *envp[])
{
    myputstr("exit", 0);
    exit(0);
}