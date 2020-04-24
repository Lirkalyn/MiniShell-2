/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** split d'unité-desu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell_2.h"

int lenght(char *str)
{
    int i = 0;

    for (i = 0; str[i] != '\0'; i++);
    return (i - 1);
}

int choose(char *line)
{
    char test[5][9] = {"cd\0", "setenv\0", "unsetenv\0", "env\0", "exit\0"};
    int ok = 0;

    for (int i = 0; i < 5; i++) { //can be remove ?
        for (int j = 0, ok = 0; test[i][j] != '\0' && line[j] != '\0'; j++) {
            if (test[i][(j + 1)] == '\0' && line[(j + 1)] != '\0')
                ok += 1;
            if (test[i][j] != line[j])
                ok += 1;
            else if ((ok == 0) && (j == lenght(test[i])))
                return i;
        }
    } // can be remove ?
    return 50;
}

char **spliter2(char **rsl , char *str)
{
    char **tmp = rsl;
    int pos = 0;
    int bool = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; str[i] != ' ' && str[i] != '\0' && str[i] != '\n'; i++)
        tmp[0][pos++] = str[i];
    pos = 0;
    for (j = (i + 1); str[j] != ' ' && str[j] != '\0' && str[j] != '\n'; j++) {
        bool = (str[j] == '-') ? 1 : bool;
        tmp[1][pos++] = str[j];
    }
    j = (bool == 0) ? i : j;
    pos = 0;
    for (k = (j + 1); str[k] != ' ' && str[k] != '\0' && str[k] != '\n'; k++)
        tmp[2][pos++] = str[k];
    return tmp;
}

char **secure(char **rsl, int i, int len, int k)
{
    char **tmp = rsl;

    tmp[0][i] = '\0';
    tmp[1][len] = '\0';
    tmp[2][k] = '\0';
    return tmp;
}

char **spliter(char *str, char **splitterd)
{
    char **rsl = splitterd;
    int bool = 0;
    int len = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    for (i = 0; str[i] != ' ' && str[i] != '\0' && str[i] != '\n'; i++);
    rsl[0] = (char *)malloc((i + 1) * sizeof(char));
    for (j = (i + 1); str[j] != ' ' && str[j] != '\0' && str[j] != '\n'; j++) {
        bool += (str[j] == '-') ? 1 : 0;
        len += 1;
    }
    rsl[1] = (char *)malloc((len + 1) * sizeof(char));
    for (k = (bool == 0) ? (i + 1) : (j + 1); (str[k] != ' ' && str[k] != '\0'
                                                && str[k] != '\n'); k++);
    k -= (bool == 0) ? (i + 1) : (j + 1);
    rsl[2] = (char *)malloc((k + 1) * sizeof(char));
    rsl = secure(rsl, i, len, k);
    return spliter2(rsl, str);
}