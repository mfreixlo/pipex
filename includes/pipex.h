/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 20:31:12 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/15 14:48:47 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "./ft_printf/includes/ft_printf.h"

typedef struct s_pipe
{
	char	**env;
	char	**paths; //libertar memoria disto
	int		pipe[2];
	int		infile;
	int		outfile;
} t_pipe;

int	clear_pipe(t_pipe *mypipe);
int	paths(t_pipe *mypipe);
int	executae(char **cmd, t_pipe mypipe);
int	files(t_pipe *mypipe, char *infile, char *outfile);
int	child1(t_pipe *mypipe, char *args);
int	child2(t_pipe *mypipe, char *args);

#endif
