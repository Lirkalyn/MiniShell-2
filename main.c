/*
** EPITECH PROJECT, 2020
** mathstick
** File description:
** stick-desu
*/

#include "include/minishell_2.h"

char **copy(char *envp[], int add, int *pos)
{
    int i = 0;
    int len = 0;
    char **rsl;

    for (len = 0; envp[len] != NULL; len++);
    rsl = (char **)malloc((len + add) * sizeof(char *));
    if (rsl == NULL)
        return NULL;
    *pos = len;
    rsl[len + (add - 1)] = NULL;
    for (i = 0; envp[i] != NULL; i++) {
        for (len = 0; envp[i][len] != '\0'; len++);
        rsl[i] = (char *)malloc((len + 1) * sizeof(char));
        if (rsl[i] == NULL)
            return NULL;
        rsl[i][len] = '\0';
        for (int j = 0; envp[i][j] != '\0'; rsl[i][j] = envp[i][j], j++);
    }
    return rsl;
}

int choice(char **envp[], cmd *cmds)
{
    switch (choose(cmds[0].bin))
    {
        case 0:
            return cd(cmds, envp);
        case 1:
            if (cmds->args_nb == 0)
                return menv(*envp);
            else
                return pre_msetenv(envp, cmds);
        case 2:
            return munsetenv(envp, cmds);
        case 3:
            return menv(*envp);
        case 4:
            return mexit();
        case 50:
            return prefork(*envp, cmds);
        default:
        break;
    }
}

char *line_cleaner(char *tmp)
{
    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] == ' ' && tmp[(i - 1)] == ' ') {
            for (int j = i; tmp[j] != '\0'; tmp[j] = tmp[(j + 1)], j++);
            i -= 2;
        }
        if (tmp[i] == '\t' && tmp[(i - 1)] != ' ' && tmp[(i + 1)] != ' ') {
            tmp[i] = ' ';
            i -= 2;
        }
        if (tmp[i] == '\t' && tmp[(i - 1)] == ' ') {
            for (int j = i; tmp[j] != '\0'; tmp[j] = tmp[(j + 1)], j++);
            i -= 2;
        }
    }
    return tmp;
}

int main(int argc, char *argv[], char *envp[])
{
    char *line = NULL;
    size_t size;
    int tmp = 0;
    char **cop = copy(envp, 1, &tmp);
    cmd *cmds;

    while (1) {
        myputstr("$>", 1);
        if ((getline(&line, &size, stdin) == -1) || cop == NULL)
            return 84;
        line = line_cleaner(line);
        if (line == NULL)
            return 84;
        cmds = cmd_filler(line, cmds);
        choice(&cop, cmds);
    }
}