#include "../includes/pipex.h"

void clear_pipe(t_pipe *mypipe)
{
	int i;

	i = 0;
	while (mypipe->paths[i])
	{
		free(mypipe->paths[i]);
		i++;
	}
	free(mypipe->paths);
}

int paths(t_pipe *mypipe)
{
	int i;
	char **paths;
//	char *aux;


	i = 0;
	while((mypipe->env)[i])
	{
		if (!ft_strncmp((*mypipe).env[i], "PATH", 4))
			paths = ft_split(&(mypipe->env[i])[5], ':');
		i++;
	}
	mypipe->paths = malloc(sizeof(char*) * i);
	i = 0;
	while (paths[i])
	{
		mypipe->paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	mypipe->paths[i] = NULL;
	return (0);
}

int executa(char **cmd, t_pipe mypipe)
{
	(void) cmd;
	int i;
	char *path;

	i = 0;
	while (mypipe.paths[i])
	{
		path = ft_strjoin(mypipe.paths[i], cmd[0]);
		if (!access(path, F_OK))
		{
			execve(path, cmd, mypipe.env);
			free(path); //se for diferente de -1 nem entra aqui, logo tenho de ver aquela cena do access para libertar esta memory :)
			return (0);
		}
		free(path);
		i++;
	}
	return (0);
}

int files(t_pipe *mypipe, char *infile, char *outfile)
{
	mypipe->infile = open(infile, O_RDONLY);
	mypipe->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);	
	if (mypipe->infile == -1 || mypipe->outfile == -1)
		return (-1);
	else
		return (0);
}

int child1(t_pipe *mypipe, char *args)
{
	char **cmd1;

	cmd1 = ft_split(args, ' ');
	close(mypipe->pipe[0]);
	dup2(mypipe->infile, STDIN_FILENO);
	dup2(mypipe->pipe[1], 1);
	close(mypipe->infile);
	executa(cmd1, *mypipe);
	exit(1);
}

int	child2(t_pipe *mypipe, char *args)
{
	char **cmd2;

	cmd2 = ft_split(args, ' ');
	close(mypipe->pipe[1]);
	dup2(mypipe->pipe[0], STDIN_FILENO);
	dup2(mypipe->outfile, 1);
	executa(cmd2, *mypipe);


	return (0);
}

int main(int argc, char **argv, char **env) {
	
	(void) argc;
	(void) argv;
	t_pipe mypipe;
	int	pid1;
	int pid2;

	mypipe.env = env;
	paths(&mypipe);
	files(&mypipe, argv[1], argv[4]);
	pipe(mypipe.pipe);
	pid1 = fork();
	if (pid1 < 0)
		return (printf("fuck\n"));
	else if (pid1 == 0) //estamos no processo filho
		child1(&mypipe, argv[2]);
	pid2 = fork();
	if (pid2 < 0)
		printf("fuck thiiiissss\n");
	else if (pid2 == 0)
		child2(&mypipe, argv[3]);
//	clear_pipe(&mypipe);
}

