/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:01:40 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 00:07:09 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int	fd;
	fd = open("testing/test1", O_RDONLY);
	if (fd == -1)
	{
		printf("open() error\n");
		return (1);
	}
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	if (close(fd) == -1)
	{
		printf("close() error\n");
		return (1);
	}
	return (0);
}