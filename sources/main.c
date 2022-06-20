/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:48:04 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/21 00:56:22 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	init_pipe(t_pipe *mypipe, int argc, char **argv, char **env)
{
	if (argc != 5)
		return (0);
	mypipe->env = env;
	paths(mypipe);
	if (files(mypipe, argv[1], argv[4]) == -1)
		return (clear_pipe(mypipe));
	pipe(mypipe->pipe);
	return (1);
}

int	main(int argc, char **argv, char **env)
{	
	t_pipe	mypipe;
	int		pid1;
	int		pid2;

	if (!init_pipe(&mypipe, argc, argv, env))
		return (0);
	pid1 = fork();
	if (pid1 < 0)
		clear_pipe(&mypipe);
	if (pid1 < 0)
		perror("Pipe error ");
	else if (pid1 == 0)
		child1(&mypipe, argv[2]);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 < 0)
		clear_pipe(&mypipe);
	if (pid2 < 0)
		perror("Pipe error ");
	else if (pid2 == 0)
		child2(&mypipe, argv[3]);
	close(mypipe.pipe[0]);
	close(mypipe.pipe[1]);
	waitpid(pid2, NULL, 0);
	return (clear_pipe(&mypipe));
}
