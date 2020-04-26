/*
** EPITECH PROJECT, 2020
** my_ls
** File description:
** h-desu
*/

#ifndef _MINISHELL_2_
#define _MINISHELL_2_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct Cmd {
    int nb;
    int pos;
    int args_nb;
    char *bin;
    char **args;
    char *path;
    char **argv;
    int pipe_left;
    int pipe_right;
} cmd;

void my_putchar(char c);
int myputstr(char *str, int opt);
int my_puterror(char *str, int opt);
int my_put_nbr(int nb);
int cd_checker(char *pathname);
int choose(char *line);
int lenght(char *str);
char **spliter(char *str, char **splitterd);
int cd(cmd *cmds, char **envp[]);
int msetenv(char **envp[], cmd *cmds);
int munsetenv(char **envp[], cmd *cmds);
int menv(char *envp[]);
int mexit(void);
char **copy(char *envp[], int add, int *pos);
char **my_str_to_word_array(char const *str);
int my_strcmp(char const *s1, char const *s2);
int prefork(char *envp[], cmd *cmds);
char *pathmaker(char *start, char *end);
int exe_checker(char *pathname);
char **arg_checker(char **arg);
cmd *cmd_filler(char *line, cmd *cmds);
cmd *pipe_finder(cmd *cmds, char **line, int pos, int opt);
int not_found(cmd cmds);
cmd *argv_filler(cmd *cmds, int pos);
int piping(cmd *cmds, char *envp[]);
int loop_forking(cmd cmds, char *envp[], int in , int out);
int last_forking(cmd cmds, char *envp[], int in);
int folder_finder(char **args, int args_nb);
int error_disp(char *name, int opt);
int cd_go_back(cmd *cmds, char **envp[], int pos);
int change_dir(char *path, char **envp[]);
int pre_msetenv(char **envp[], cmd *cmds);
void error_signal(int pid, int error);

#endif
