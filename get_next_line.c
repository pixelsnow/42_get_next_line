/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:55 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 14:19:39 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TODO: think about data types 
// #include <stdio.h>

char	*append_line(char *old_res, char *buf, int start, int len)
{
	int		i;
	char	*res;

	res = (char *)malloc(sizeof(char)
			* (ft_strlen(old_res) + len + 1));
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

// If 0 is returned from this function,
// 		nothing was read and res needs to be retuned
// If 1 is returned, data was read to buffer and the process can continue
int	read_to_buf(int fd, char **res, char *buf)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == 0 && (**res))
		return (0);
	if (ret <= 0)
	{
		free(*res);
		*res = NULL;
		return (0);
	}
	buf[ret] = '\0';
	return (1);
}

char	*finish_line(char *res, char *buf, int *line_start, int *line_len)
{
	res = append_line(res, buf, *line_start, *line_start);
	*line_start += *line_len;
	*line_len = 0;
	return (res);
}

int	add_buf_to_res(char **res, char *buf, int *line_start, int *line_len)
{
	*res = append_line(*res, buf, *line_start, BUFFER_SIZE - *line_start);
	if (!*res)
		return (0);
	*line_start = 0;
	*line_len = 0;
	return (1);
}

//return (finish_line(res, buf, &line_start, &line_len));
char	*get_next_line(int fd)
{
	char		*res;
	static char	buf[BUFFER_SIZE + 1];
	static int	line_start = 0;
	static int	line_len = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || !init_res(&res))
		return (NULL);
	while (!line_len)
	{
		if (!line_start)
			if (!read_to_buf(fd, &res, buf))
				return (res);
		line_len = find_newline(buf, line_start) - line_start;
		if (line_len > 0)
		{
			res = append_line(res, buf, line_start, line_len);
			line_start += line_len;
			line_len = 0;
			return (res);
		}
		else if (!add_buf_to_res(&res, buf, &line_start, &line_len))
			return (NULL);
	}
	return (NULL);
}
