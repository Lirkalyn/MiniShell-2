/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** ok-desu
*/

#include "../include/minishell_2.h"

void my_error_signal(int error)
{
    if (WTERMSIG(error) == SIGABRT)
        my_puterror("Abort", 0);
    if (WTERMSIG(error) == SIGSEGV)
        my_puterror("Segmentation fault (core dumped)", 0);
    if (WTERMSIG(error) == SIGFPE)
        my_puterror("Floating exception", 0);
    if (WTERMSIG(error) == SIGTERM)
        my_puterror("Terminated", 0);
    if (WTERMSIG(error) == SIGKILL)
        my_puterror("Killed", 0);
    if (WTERMSIG(error) == SIGTRAP)
        my_puterror("trace trap", 0);
    if (WTERMSIG(error) == SIGQUIT)
        my_puterror("Quit", 0);
    if (WTERMSIG(error) == SIGSTOP)
        my_puterror("Stopped", 0);
    if (WTERMSIG(error) == SIGILL)
        my_puterror("illegal hardware instruction", 0);
    if (WTERMSIG(error) == SIGBUS)
        my_puterror("Bus error", 0);
}