/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:38:19 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/20 11:23:38 by mfreixo-         ###   ########.fr       */
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

void	put_error(char *str, char *file)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
