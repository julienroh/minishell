/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:22:52 by jroh              #+#    #+#             */
/*   Updated: 2025/10/20 10:37:55 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_stash(int fd, char *stash, char *buffer)
{
	char	*temp;
	ssize_t	reading;

	reading = 1;
	while (reading > 0)
	{
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (reading == 0)
			break ;
		buffer[reading] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

int	ft_strlen_endline(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

char	*line_to_write(char *str)
{
	char	*line;

	if (!str)
		return (NULL);
	line = ft_substr(str, 0, ft_strlen_endline(str) + 1);
	return (line);
}

char	*left_line(char *str)
{
	int		i;
	char	*left;

	i = ft_strlen_endline(str);
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	if (str[i] == 0 || str[i + 1] == 0)
	{
		free(str);
		return (NULL);
	}
	left = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	free(str);
	return (left);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(stash);
		buffer = NULL;
		stash = NULL;
		return (NULL);
	}
	stash = fill_stash(fd, stash, buffer);
	free(buffer);
	buffer = NULL;
	if (!stash)
		return (NULL);
	line = line_to_write(stash);
	stash = left_line(stash);
	return (line);
}
