/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:55 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/26 23:40:48 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

// TODO: make sure to handle std input as well

int	find_newline(char buf[BUFFER_SIZE + 1], int start_index)
{
	/* if (start_index < 0)
		start_index = 0; */
	while (buf[start_index])
	{
		if (buf[start_index] == '\n')
			return (start_index);
		start_index++;
	}
	return (-1);
}

char	*read_file(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*res;
	static int	line_start = 0;
	static int	line_len = -1; // Can it be 0?
	int			ret;

	// Possibly make a separate init function
	res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	while (line_len < 0)
	{
		if (!line_start)
		{
			ret = read(fd, buf, BUFFER_SIZE);
			if (ret < 0)
				return (NULL);
			if (!ret)
			{
				return (res);
			}
			buf[ret] = '\0';
		}
		line_len = find_newline(buf, line_start);
		// If newline was found in buffer, result will be returned here
		if (line_len >= 0)
		{
			// Two different append functions? Think about input
			// Or just send BUFFER_SIZE - line_start
			if (!append_line(res, buf, line_start, line_len))
				return (NULL);
			line_start += line_len; // only OK if line_start is 0 not -1
			line_len = -1;
			return (res);
		}
		else
		{
			// if newline wasn't found in the buffer,
			// append the rest of the buffer to result
			if (!append_line(res, buf, line_start, BUFFER_SIZE))
				return (NULL);
			// Reset line start
			line_start = 0; // or -1?
			line_len = -1;
		}
	}
	printf("%s\n%d\n", buf, ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	return (read_file(fd));
}
