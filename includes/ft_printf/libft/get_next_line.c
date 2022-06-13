/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:38:31 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/11 15:50:26 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_read(int fd, char *buffer)
{
	int	n;

	if (fd < 0)
	{
		free(buffer);
		return (-1);
	}
	n = read(fd, NULL, 0);
	if (n == -1 || BUFFER_SIZE <= 0 || fd < 0)
	{
		free(buffer);
		return (-1);
	}
	else
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[n] = '\0';
	}
	return (n);
}

char	*get_line(int fd)
{
	char	*buffer;
	int		n;
	char	*aux;
	char	*str;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	n = ft_read(fd, buffer);
	if (n == -1)
	{
		return (NULL);
	}
	aux = NULL;
	while (n > 0)
	{
		str = ft_strjoin_gnl(aux, buffer);
		aux = ft_strdup_gnl(str);
		free(str);
		if (ft_newline(aux) != -1)
			break ;
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		n = ft_read(fd, buffer);
	}
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			i;
	int			n;

	if (buffer == NULL)
		buffer = get_line(fd);
	if (buffer == NULL)
		return (NULL);
	n = ft_newline(buffer);
	if (n == -1)
		buffer = ft_strjoin_gnl(buffer, get_line(fd));
	if (n == -1)
		n = ft_strlen_gnl(buffer);
	line = malloc(sizeof(char) * (n + 2));
	i = 0;
	while (buffer[i])
	{
		line[i] = buffer[i];
		if (buffer[i++] == '\n')
			break ;
	}
	line[i] = '\0';
	buffer = ft_save_buff(buffer, i);
	return (line);
}
