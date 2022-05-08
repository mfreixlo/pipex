#include "./includes/ft_printf/includes/ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/errno.h>

typedef struct s_pipe
{
    char **cmd_lst;
	char *cmd_path;
    char **envp;
} t_pipe;
