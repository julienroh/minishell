/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jroh <jroh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:01:27 by haoky             #+#    #+#             */
/*   Updated: 2025/11/21 15:01:33 by jroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*gnl_ft_strdup(const char *s1);
int		gnl_ft_strlen(const char *s);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
char	*gnl_ft_strjoin(char const *s1, char const *s2);
char	*gnl_ft_strchr(const char *s, int c);

#endif
