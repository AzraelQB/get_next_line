/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awooden <awooden@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:24:06 by awooden           #+#    #+#             */
/*   Updated: 2022/02/20 14:36:46 by awooden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*cut_until_endl(int fd, char **saved)
{
	int		len;
	char	*res;
	char	*tmp;

	len = 0;
	while (saved[fd][len] != '\n' && saved[fd][len] != '\0')
		++len;
	if (saved[fd][len] == '\n')
	{
		res = ft_substr(saved[fd], 0, len + 1);
		tmp = ft_strdup(saved[fd] + len + 1);
		free(saved[fd]);
		saved[fd] = tmp;
		return (res);
	}
	else
	{
		res = ft_strdup(saved[fd]);
		free(saved[fd]);
		saved[fd] = NULL;
		return (res);
	}
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_MAX];
	int			bytes_read;
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;

	bytes_read = 1;
	if (fd < 0 || fd > FD_MAX || read(fd, NULL, 0) < 0)
		return (NULL);
	(saved[fd] == NULL) && (saved[fd] = ft_strdup("\0"));
	while (ft_strchr(saved[fd], '\n') == NULL && bytes_read)
	{	
		bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[bytes_read] = '\0';
		tmp = ft_strjoin(saved[fd], buff);
		free(saved[fd]);
		saved[fd] = tmp;
	}
	if (saved[fd][0] == '\0')
	{
		free(saved[fd]);
		saved[fd] = NULL;
		return (NULL);
	}
	return (cut_until_endl(fd, saved));
}
