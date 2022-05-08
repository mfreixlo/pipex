#include "../pipex.h"

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

void del_clist(char **char_list)
{
	int i;

	i = 0;
	while (char_list[i])
	{
		free(char_list[i]);
		i++;
	}
	free(char_list);
}



void del_pipe(t_pipe *pipe)
{
	int i;

	free(pipe->cmd_path);
	i = 0;
	while (pipe->cmd_lst[i])
	{
		free(pipe->cmd_lst[i]);
		i++;
	}
	free(pipe->cmd_lst);
}

int check_access(t_pipe *pipe)
{
	int i;
	char **paths;
	char *cmd;
	char *aux;
	
	i = 0;
	paths = ft_split(pipe->cmd_path, ':');
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(aux, pipe->cmd_lst[0]);
		free(aux);
		if (!access(cmd, F_OK))
		{
			free(pipe->cmd_path);
			pipe->cmd_path = ft_strdup(cmd);
			free(cmd);
			del_clist(paths);
			return (1);
		}
		else
			free(cmd);
		i++;
	}
	del_clist(paths);
	return (0);
}

/*paths = search on the environment the line corresponding to paths, adds it to the struct pipe*/
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
	pipe->cmd_path = path;
	check_access(pipe);
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
	}
	pipe.cmd_lst = ft_split(argv[2], ' ');
	paths(&pipe, envp);
	printf("%s\n", pipe.cmd_path);
	execve(pipe.cmd_path, ft_split(argv[2], ' '), envp);
	del_pipe(&pipe);
	return (0);
}
