/*
** EPITECH PROJECT, 2020
** minishell_2
** File description:
** very_little-desu
*/

#include "../include/minishell_2.h"

int isbar(char *bin, char *check)
{
    int i = 0;
    int pos = -1;

    if (check != NULL)
        return pos;
    else {
        for (; bin[i] != '\0'; i++)
            if (bin[i] == '/')
                pos = i;
    }
    return pos;
}

char *ppath(char *bin)
{
    struct stat sb;
    char *path = NULL;
    int i = 0;
    int pos = -1;

    if (exe_checker(pathmaker(getcwd(NULL, 0), bin)) == 0)
        return pathmaker(getcwd(NULL, 0), bin);
    if (bin[0] == '.' && bin[1] == '/')
        if (exe_checker(pathmaker(getcwd(NULL, 0), (bin + 2))) == 0)
            path = pathmaker(getcwd(NULL, 0), (bin + 2));
    if (bin[0] == '/' && exe_checker(bin) == 0) {
        stat(bin, &sb);
        if (S_ISDIR(sb.st_mode) == 0)
            path = bin;}
    if (isbar(bin, path) != -1)
        path = pathmaker(getcwd(NULL, 0), bin);
    if (exe_checker(path) == 0)
        return path;
    else
        return NULL;
}