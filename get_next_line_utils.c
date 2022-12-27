/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:54:32 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 14:17:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(char *buf, int start_index)
{
	while (buf[start_index])
	{
		if (buf[start_index] == '\n')
			return (start_index + 1);
		start_index++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

int	init_res(char **res)
{
	*res = (char *)malloc(sizeof(char) * 1);
	if (!*res)
		return (0);
	(*res)[0] = '\0';
	return (1);
}
