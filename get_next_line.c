/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:55 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 15:35:05 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TODO: think about data types 

// Allocates enough memory for new result, copies old result and additional
// chars from buffer to new memory, frees memory from old result
static char	*append_line(char *old_res, char *buf, ssize_t start, ssize_t len)
{
	ssize_t		i;
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
// 		nothing was read and res needs to be returned (or NULL)
// 		It can either mean that EOF was reached and result is ready,
// 		or that reading from file failed and there was an error.
// If 1 is returned, data was read to buffer and the process can continue
static int	read_to_buf(int fd, char **res, char *buf)
{
	ssize_t	ret;

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

// This function is called when a newline was found in buffer
// 		and therefore it's time to add the last chunk to result and return it.
// line_start is set to the next character after newline,
// line_len is set to 0 in preparation for next get_next_line() call.
static char	*finish_line(char *res, char *buf, ssize_t *line_start, ssize_t *line_len)
{
	res = append_line(res, buf, *line_start, *line_len);
	*line_start += *line_len;
	*line_len = 0;
	return (res);
}

// This function is called when no newline was found in buffer
// 		and therefore all we need to do is append buffer to result.
// It returns 0 in case or error (malloc fail), returns 1 if success.
// line_start and line_len values are also reset
//		in preparation for next buffer read.
static int	add_buf_to_res(char **res, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	*res = append_line(*res, buf, *line_start, BUFFER_SIZE - *line_start);
	if (!*res)
		return (0);
	*line_start = 0;
	*line_len = 0;
	return (1);
}

// line_len indicates index in the buffer
//		after the end of the current line.
// line_start indicates index in the buffer
//		from which the next line should be started to be read.
//		0 value indicates that new info needs to be read to buffer.
// First obvious errors are handled
// 		and res is initialised as an empty string.
// New data is being read to buffer and added to res until either
//		newline is found or EOF is reached (or error happened)
// If newline was found, it and everything before it is added to res
//		and res is returned.
// If EOF reached and there was something in res, res is returned,
//		otherwise NULL is returned.
char	*get_next_line(int fd)
{
	char			*res;
	static char		buf[BUFFER_SIZE + 1];
	static ssize_t	line_start = 0;
	static ssize_t	line_len = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || !init_res(&res))
		return (NULL);
	while (!line_len)
	{
		if (!line_start && !read_to_buf(fd, &res, buf))
				return (res);
		line_len = find_newline(buf, line_start) - line_start;
		if (line_len > 0)
			return (finish_line(res, buf, &line_start, &line_len));
		else if (!add_buf_to_res(&res, buf, &line_start, &line_len))
			return (NULL);
	}
	return (NULL);
}
