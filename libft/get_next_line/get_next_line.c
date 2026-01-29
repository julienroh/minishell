/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:54:59 by haoky             #+#    #+#             */
/*   Updated: 2025/11/21 15:02:49 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_stash(int fd, char *stash, char *buffer);
static char	*line_to_write(char *str);
static int	ft_strlen_endline(char *str);
static char	*left_line(char *str);

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

static char	*fill_stash(int fd, char *stash, char *buffer)
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
			stash = gnl_ft_strdup("");
		temp = stash;
		stash = gnl_ft_strjoin(temp, buffer);
		free(temp);
		if (gnl_ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

static char	*line_to_write(char *str)
{
	char	*line;

	if (!str)
		return (NULL);
	line = gnl_ft_substr(str, 0, ft_strlen_endline(str) + 1);
	return (line);
}

static int	ft_strlen_endline(char *str)
{
	int	i;

	i = 0;
	while (i < gnl_ft_strlen(str))
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

static char	*left_line(char *str)
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
	left = gnl_ft_substr(str, i + 1, gnl_ft_strlen(str) - i - 1);
	free(str);
	return (left);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*to_print;
// 	int		i;	
// 	i = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	while (i < 5)
// 	{
// 		to_print = get_next_line(fd);
// 		printf ("ligne numero %d : %s", i, to_print);
// 		i++;
// 	}
// 	return (0);
// }