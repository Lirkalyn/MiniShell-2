/*
** EPITECH PROJECT, 2020
** minishell 2
** File description:
** cmd-desu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

cmd *bin_filler(cmd *cmds, char **line, int pos)
{
    int len = 0;

    for (len = 0; line[0][len] != '\0' && line[0][len] != '\n'
                && line[0][len] != ' ' && line[0][len] != '|'; len++);
    cmds[pos].bin = malloc((len + 1) * sizeof(char));
    if (cmds[pos].bin == NULL)
        return NULL;
    cmds[pos].bin[len] = '\0';
    for (int i = 0; i < len; i++)
        cmds[pos].bin[i] = line[0][i];
    *line = (*line + (len + 1));
    return cmds;
}

cmd *args_filler_real(cmd *cmds, char **line, int pos)
{
    int arg_pos = 0;
    int len = 0;

    while (line[0][0] != '\0' && line[0][0] != '\n' && line[0][0] != '|'
            && arg_pos < cmds[pos].args_nb)
        if (line[0][0] != ' ') {
            for (len = 0; line[0][len] != ' ' && line[0][len] != '\0'
                        && line[0][len] != '\n' && line[0][len] != '|'; len++);
            cmds[pos].args[arg_pos] = malloc((len + 1) * sizeof(char));
            if (cmds[pos].args[arg_pos] == NULL)
                return NULL;
            cmds[pos].args[arg_pos][len] = '\0';
            for (int i = 0; i < len; i++)
                cmds[pos].args[arg_pos][i] = line[0][i];
            arg_pos += 1;
            line[0] = (line[0] + (len + 1));
        }
        else
            line[0] += 1;
    return cmds;
}

cmd *args_filler(cmd *cmds, char **line, int pos)
{
    int arg_nb = 0;
    int len = 0;
    char *tmp = NULL;

    tmp = line[0];
    while (tmp[0] != '\0' && tmp[0] != '\n' && tmp[0] != '|')
        if (tmp[0] != ' ') {
            arg_nb += 1;
            for (len = 0; tmp[len] != ' ' && tmp[len] != '\0'
                        && tmp[len] != '\n' && tmp[len] != '|'; len++);
            tmp = (tmp + (len + 1));
        }
        else
            tmp += 1;
    cmds[pos].args = malloc(arg_nb * sizeof(char *));
    cmds[pos].args_nb = arg_nb;
    if (cmds[pos].args == NULL)
        return NULL;
    else
        return args_filler_real(cmds, line, pos);
}

cmd *initializer(int nb, cmd *cmds)
{
    int i = 0;

    cmds = malloc(nb * sizeof(cmd));
    if (cmds == NULL)
        return NULL;
    for (i = 0; i < nb; i++) {
        cmds[i].nb = nb;
        cmds[i].pos = i;
        cmds[i].args_nb = 0;
        cmds[i].bin = NULL;
        cmds[i].args = NULL;
        cmds[i].pipe_left = 0;
        cmds[i].pipe_right = 0;
    }
    return cmds;
}

cmd *cmd_filler(char *line, cmd *cmds)
{
    int nb = 1;
    int i = 0;

    for (i = 0; line[i] != '\0' && line[i] != '\n'; i++)
        nb += (line[i] == '|') ? 1 : 0;
    cmds = initializer(nb, cmds);
    if (cmds == NULL)
        return NULL;
    for (i = 0; i < nb; i++) {
        cmds = pipe_finder(cmds, &line, i, 1);
//        printf("line = %s", line);
        cmds = bin_filler(cmds, &line, i);
        if (cmds == NULL)
            return NULL;
        cmds = args_filler(cmds, &line, i);
        if (cmds == NULL)
            return NULL;
        cmds = pipe_finder(cmds, &line, i, 2);
    }
/*    printf("\n");
    for (i = 0; i < nb; i++) {
        printf("%s\n", cmds[i].bin);
        for (int j = 0; j < cmds[i].args_nb; j++)
            printf("%d = %s\n", i, cmds[i].args[j]);
        printf("left = %d\n", cmds[i].pipe_left);
        printf("right = %d\n", cmds[i].pipe_right);
        printf("\n\n");
    }*/
    return cmds;
}