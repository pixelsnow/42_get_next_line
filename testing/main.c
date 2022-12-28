/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:01:40 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/28 15:27:24 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;

	fd = open("testing/bible.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("open() error\n");
		return (1);
	}
	char *res;
	res = get_next_line(fd);
	printf("%s\n", res);
	free(res);
	while (res)
	{
		res = get_next_line(fd);
		printf("%s\n", res);
		free(res);
	}
	if (close(fd) == -1)
	{
		printf("close() error\n");
		return (1);
	}
	return (0);
}
