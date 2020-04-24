/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** more_cmd-desu
*/

#include "../include/minishell_2.h"

cmd *pipe_finder(cmd *cmds, char **line, int pos, int opt)
{
    int i;

    if ((opt == 1) && (line[0][0] == '|')) {
        cmds[pos].pipe_left = 1;
        while (line[0][0] == ' ' || line[0][0] == '|')
            line[0] += 1;
    }
    if ((opt == 2) && (line[0][0] == '|'))
        cmds[pos].pipe_right = 1;
    return cmds;
}