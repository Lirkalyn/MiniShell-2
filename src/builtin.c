/*
** EPITECH PROJECT, 2020
** minishell1
** File description:
** the sequel-desu
*/

#include "../include/minishell_2.h"

int folder_finder(char **args, int args_nb)
{
    int i = 0;
    int j = 0;

    if (args_nb == 1) {
        for (; args[0][j] != '\0'; j++);
        if (j == 1 && args[0][0] == '-')
            return -5;
    }
    for (; i < args_nb; i++) {
        if (args[i][0] != '-')
            return i;
    }
    return -84;
}

int error_disp(char *name, int opt)
{
    if (opt == 0) {
        myputstr(name, 2);
        myputstr(": Permission denied.", 0);
    }
    if (opt  == 1)
        myputstr("error : no folder found in your input.", 0);
    if (opt == 2)
        myputstr("error in setenv : please check the arguments.", 0);
    if (opt == 3)
        myputstr("error in unsetenv : please check the arguments.", 0);
    if (opt == 4)
        myputstr("error in cd - : OLDPWD not set.", 0);
    return 84;
}

int mexit(void)
{
    myputstr("exit", 0);
    exit(0);
}