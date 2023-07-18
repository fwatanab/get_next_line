/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:31:58 by fwatanab          #+#    #+#             */
/*   Updated: 2023/05/12 16:06:00 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*keep_line(char *keep)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (keep[i] && keep[i] != '\n')
		i++;
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(keep) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (keep[i])
		str[j++] = keep[i++];
	str[j] = '\0';
	free(keep);
	return (str);
}

char	*get_line(char *keep)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] && keep[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (keep[i] && keep[i] != '\n')
	{
		str[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		str[i] = '\n';
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*read_fd(int fd, char *keep)
{
	char	*buff;
	ssize_t	byte;
	size_t	i;

	i = 0;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte = 1;
	while (!ft_strchr(keep, '\n') && byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		keep = ft_strjoin(keep, buff, i);
	}
	free(buff);
	return (keep);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*keep;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = read_fd(fd, keep);
	if (!keep)
		return (NULL);
	line = get_line(keep);
	keep = keep_line(keep);
	return (line);
}
