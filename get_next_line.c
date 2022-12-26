/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:53:55 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/26 17:41:46 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


// Handle std input

char	*read_file(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	printf("%s\n%d\n", buf, ret);
	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = '\0';
	printf("%s\n%d\n", buf, ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	if (fd == -1 || BUFFER_SIZE < 1)
	{
		return (NULL);
	}
	return (read_file(fd));
}
