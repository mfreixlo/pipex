/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:48:04 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/15 15:20:38 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	clear_pipe(t_pipe *mypipe)
{
	int	i;

	i = 0;
	if (!mypipe->paths || !mypipe->paths[0])
		return (0);
	while (mypipe->paths[i])
	{
		free(mypipe->paths[i]);
		i++;
	}
	free(mypipe->paths);
	return (0);
}

void	clear_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

int	paths(t_pipe *mypipe)
{
	int		i;
	char	**paths;

	i = 0;
	while ((mypipe->env)[i])
	{
		if (!ft_strncmp((*mypipe).env[i], "PATH", 4))
			paths = ft_split(&(mypipe->env[i])[5], ':');
		i++;
	}
	mypipe->paths = malloc(sizeof(char *) * i);
	if (!(mypipe->paths))
		return (-1);
	i = 0;
	while (paths[i])
	{
		mypipe->paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	clear_split(&paths);
	mypipe->paths[i] = NULL;
	return (0);
}

int	executa(char **cmd, t_pipe mypipe)
{
	int		i;
	char	*path;

	i = 0;
	while (mypipe.paths[i])
	{
		path = ft_strjoin(mypipe.paths[i], cmd[0]);
		if (!access(path, F_OK))
		{
			execve(path, cmd, mypipe.env);
			free(path);
			return (0);
		}
		free(path);
		i++;
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void put_error(char *str, char *file)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	files(t_pipe *mypipe, char *infile, char *outfile)
{
	char	**str;

	if (access(infile, F_OK) == -1)
	{
		str = ft_split(infile, ' ');
		put_error("zsh: no such file or directory: ", infile);
		clear_split(&str);
		return (-1);
	}
	mypipe->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (access(outfile, W_OK) == -1)
	{
		put_error("zsh: permission denied: ", outfile);
		return (-1);
	}
	if (access(infile, R_OK) == -1)
	{
		put_error("zsh: permission denied: ", infile);
		return (-1);
	}
	mypipe->infile = open(infile, O_RDONLY);
	if (mypipe->infile == -1 || mypipe->outfile == -1)
		return (-1);
	else
		return (0);
}

int	child1(t_pipe *mypipe, char *args)
{
	char	**cmd1;

	cmd1 = ft_split(args, ' ');
	close(mypipe->pipe[0]);
	dup2(mypipe->infile, STDIN_FILENO);
	dup2(mypipe->pipe[1], STDOUT_FILENO);
	close(mypipe->infile);
	executa(cmd1, *mypipe);
	exit(0);
}

int	child2(t_pipe *mypipe, char *args)
{
	char	**cmd2;

	cmd2 = ft_split(args, ' ');
	close(mypipe->pipe[1]);
	dup2(mypipe->pipe[0], STDIN_FILENO);
	dup2(mypipe->outfile, STDOUT_FILENO);
	close(mypipe->outfile);
	close(mypipe->pipe[1]);
	executa(cmd2, *mypipe);
	exit(0);
}

int	main(int argc, char **argv, char **env)
{	
	t_pipe	mypipe;
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (0);
	mypipe.env = env;
	paths(&mypipe);
	if (files(&mypipe, argv[1], argv[4]) == -1)
		return (clear_pipe(&mypipe));
	pipe(mypipe.pipe);
	pid1 = fork();
	if (pid1 < 0)
	{
		clear_pipe(&mypipe);
		perror("Pipe error ");
	}
	else if (pid1 == 0)
		child1(&mypipe, argv[2]);
	pid2 = fork();
	if (pid2 < 0)
	{
		clear_pipe(&mypipe);
		perror("Pipe error ");
	}
	else if (pid2 == 0)
		child2(&mypipe, argv[3]);
	close(mypipe.pipe[0]);
	close(mypipe.pipe[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
