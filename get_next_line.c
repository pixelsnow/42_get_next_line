/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:55 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 00:48:30 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// TODO: make sure to handle std input as well
// TODO: think about data types

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

char	*append_line(char *old_res, char buf[BUFFER_SIZE + 1], int start, int len)
{
	int		i;
	char	*res;

	res = (char	*)malloc(sizeof(char) *
		(ft_strlen(old_res) + len + 1));
	if (!res)
	{
		free(old_res);
		return (NULL);
	}
	i = 0;
	while (old_res[i])
	{
		res[i] = old_res[i];
		i++;
	}
	free(old_res);
	res[i + len] = '\0';
	while (len)
	{
		len--;
		res[i + len] = buf[start + len];
	}
	return (res);
}

int	find_newline(char buf[BUFFER_SIZE + 1], int start_index)
{
	while (buf[start_index])
	{
		if (buf[start_index] == '\n')
			return (start_index + 1);
		start_index++;
	}
	return (0);
}

char	*read_file(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*res;
	static int	line_start = 0;
	static int	line_len = 0; // Can it be 0?
	int			ret;

	// Possibly make a separate init function
	res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (!line_len)
	{
		if (!line_start)
		{
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret < 0)
			{
				free(res);
				return (NULL);
			}
			if (!ret)
			{
				if (res[0])
					return (res);
				free(res);
				return (NULL);
			}
			buf[ret] = '\0';
		}
		line_len = find_newline(buf, line_start) - line_start;
		if (line_len > 0)
		{
			res = append_line(res, buf, line_start, line_len);
			if (!res)
				return (NULL);
			line_start += line_len;
			line_len = 0;
			return (res);
		}
		else
		{
			res = append_line(res, buf, line_start, BUFFER_SIZE - line_start);
			if (!res)
				return (NULL);
			line_start = 0;
			line_len = 0;
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	return (read_file(fd));
}
