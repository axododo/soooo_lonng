/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:24:32 by mguilber          #+#    #+#             */
/*   Updated: 2025/11/27 16:20:18 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../so_long.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

static char	*read_buffer(int fd, char *str)
{
	char	*buffer;
	int		nby;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	nby = read(fd, buffer, BUFFER_SIZE);
	while (nby > 0)
	{
		buffer[nby] = '\0';
		str = join_and_free(str, buffer);
		if (!str || ft_strchr(str, '\n') >= 0)
			break ;
		nby = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (nby < 0)
		return (free(str), NULL);
	return (str);
}

static char	*extract_line(char *str, char **rest)
{
	int		pos;
	char	*line;
	char	*tmp;

	pos = ft_strchr(str, '\n');
	if (pos >= 0)
	{
		line = ft_substr(str, 0, pos + 1);
		tmp = ft_substr(str, pos + 1, ft_strlen(str + pos + 1));
		free(str);
		if (*rest)
			free(*rest);
		*rest = tmp;
		return (line);
	}
	if (*rest)
		free(*rest);
	*rest = NULL;
	return (str);
}

static char	*init_str(char *rest)
{
	char	*str;

	if (rest)
		str = ft_strjoin("", rest);
	else
		str = ft_strjoin("", "");
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = init_str(rest);
	if (!str)
		return (NULL);
	if (rest && ft_strchr(rest, '\n') >= 0)
	{
		free(rest);
		rest = NULL;
		return (extract_line(str, &rest));
	}
	if (rest)
	{
		free(rest);
		rest = NULL;
	}
	str = read_buffer(fd, str);
	if (!str || str[0] == '\0')
		return (free(str), NULL);
	return (extract_line(str, &rest));
}
