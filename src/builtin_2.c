/*
** EPITECH PROJECT, 2020
** minishell_2
** File description:
** yolo-desu
*/

#include "../include/minishell_2.h"

int folder_finder(char **args, int args_nb)
{
    int i = 0;

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
        myputstr(": Permission denied", 0);
    }
//    if (opt  == 1)
//        myputstr("error : no folder found in your input", 0);
    if (opt == 2)
        myputstr("error in setenv : please check the arguments", 0);
    if (opt == 3)
        myputstr("error in unsetenv : please check the arguments", 0);
    return 84;
}