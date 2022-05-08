#include "../includes/ft_printf/includes/ft_printf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/errno.h>

typedef struct s_pipe
{
	char *path;
} t_pipe;

int check_error(char *file, int in_out) //in = 0, out = 1
{
	int mode;

	if (in_out == 0)
	{
		mode = access(file, R_OK);
		if (errno != 0)
		{
			ft_printf("zsh: %s: %s\n", strerror(errno), file);
			return (0);
		}
	}
	if (in_out == 1)
	{
		mode = access(file, W_OK);
		if (errno != 0)
		{
			ft_printf("zsh: %s: %s\n", strerror(errno), file);
			return (0);
		}
	}
	return (1);
}

void pipex(char **argv)
{
	int fd;
	int mode;

	fd = open(argv[1], O_RDONLY);
	mode = access(argv[4], R_OK);
	if (errno != 0)
	{
		ft_printf("%d\n", errno);
		ft_printf("zsh: %s: %s\n", strerror(errno), argv[1]);
	}
	close(fd);
}

void paths(t_pipe *pipe, char **envp)
{
	int i;
	char *path;

	i = 0;
	while (envp[i] && strncmp("PATH", envp[i], 4))
	{
		i++;
	}
	path = ft_strdup(&(envp[i][5]));
	pipe->path = path;
}

void del_pipe(t_pipe *pipe)
{
	free(pipe->path);
}


int main(int argc, char **argv, char **envp)
{
	(void) envp;
	t_pipe pipe;
	
	if (argc != 5)
		return (0);
	else
	{
		if (!check_error(argv[1], 0))
			return (0);
		if (!check_error(argv[4], 1))
			return (0);
		pipex(argv);
	}
	paths(&pipe, envp);
	printf("%s\n", pipe.path);
	del_pipe(&pipe);
	return (0);
}
