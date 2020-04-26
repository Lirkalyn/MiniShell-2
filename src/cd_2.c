/*
** EPITECH PROJECT, 2020
** minishell_2
** File description:
** more cd-desu
*/

#include "../include/minishell_2.h"

int cd_setenv_lenght(char *str, char *str2)
{
    int len = 0;
    int men = 0;

    for (; str[len] != '\0'; len++);
    for (; str2[men] != '\0'; men++);
    return (len + men);
}

static int cd_setenv(char **envp[], char *str, char *str2)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int len = cd_setenv_lenght(str, str2);
    int pos = -5;
    char **rsl = copy(*envp, 2, &pos);

    for (; envp[0][k] != NULL; k++)
        free(envp[0][k]);
    free(envp[0][k]);
    if (rsl == NULL || pos == -5 || len == -84)
        return error_disp(NULL, 2);
    rsl[pos] = (char *)malloc((len + 2) * sizeof(char));
    rsl[pos][(len + 1)] = '\0';
    for (; str[i] != '\0'; rsl[pos][i] = str[i], i++);
    rsl[pos][i++] = '=';
    for (; str2[j] != '\0'; rsl[pos][i++] = str2[j++]);
    *envp = rsl;
}

static int pre_cd_setenv(char **envp[], char *str, char *str2, int where)
{
    int i = 0;
    int j = 0;
    int len = cd_setenv_lenght(str, str2);
    char *tmp = NULL;

    if (where == -1)
        return cd_setenv(envp, str, str2);
    tmp = malloc((len + 2) * sizeof(char));
    if (tmp == NULL)
        return 84;
    tmp[len + 1] = '\0';
    for (i = 0; str[i] != '\0'; tmp[i] = str[i], i++);
    tmp[i++] = '=';
    for (; str2[j] != '\0'; tmp[i++] = str2[j++]);
    envp[0][where] = tmp;
}

int cd_go_back(cmd *cmds, char **envp[], int pos)
{
    int i = 0;
    int where = -1;
    char *tmp = NULL;

    if (pos == -84)
        return 84;
    else {
        for (; envp[0][i] != NULL; i++)
            where = (my_strcmp(envp[0][i], "OLDPWD=\0") == 0) ? i : where;
        if (where != -1)
            return change_dir((envp[0][where] + 7), envp);
        else
            return error_disp(NULL, 4);
        return 1;
    }
}

int change_dir(char *path, char **envp[])
{
    int i = 0;
    int where = -1;
    char *tmp = NULL;
    int ok = 0;

    for (; envp[0][i] != NULL; i++)
        where = (my_strcmp(envp[0][i], "OLDPWD=\0") == 0) ? i : where;
    ok = pre_cd_setenv(envp, "OLDPWD\0", getcwd(NULL, 0), where);
    if (ok == 84)
        return 84;
    else
        return chdir(path);
}