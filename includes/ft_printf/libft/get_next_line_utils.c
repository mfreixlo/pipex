/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 09:38:53 by mfreixo-          #+#    #+#             */
/*   Updated: 2022/06/11 15:51:07 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			i++;
		}
	}
	return (i);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	int		i;
	char	*new;
	int		k;

	new = malloc(sizeof(char) * (ft_strlen_gnl(str1)
				+ ft_strlen_gnl(str2) + 1));
	k = 0;
	i = 0;
	if (str1)
		while (str1[i])
			new[k++] = str1[i++];
	i = 0;
	if (str2)
		while (str2[i])
			new[k++] = str2[i++];
	new[k] = '\0';
	free(str2);
	free(str1);
	return (new);
}

char	*ft_strdup_gnl(char *str)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen_gnl(str) + 1));
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_save_buff(char *buffer, int pos)
{
	char	*aux;

	if (pos == ft_strlen_gnl(buffer))
	{
		free(buffer);
		return (NULL);
	}
	aux = ft_strdup_gnl(&buffer[pos]);
	free(buffer);
	return (aux);
}
