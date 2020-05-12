/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** ok-desu
*/

#include "../include/minishell_2.h"

void my_error_signal(int error)
{
    if (error == SIGABRT)
        my_puterror("Abort", 0);
    if (error == 139)
        my_puterror("Segmentation fault (core dumped)", 0);
    if (error == SIGFPE)
        my_puterror("floating point exception", 0);
    if (error == SIGTERM)
        my_puterror("Terminated", 0);
    if (error == SIGKILL)
        my_puterror("Killed", 0);
    if (error == SIGTRAP)
        my_puterror("trace trap", 0);
    if (error == SIGQUIT)
        my_puterror("Quit", 0);
    if (error == SIGSTOP)
        my_puterror("Stopped", 0);
    if (error == SIGILL)
        my_puterror("illegal hardware instruction", 0);
}