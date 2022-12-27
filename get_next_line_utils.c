/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:54:32 by vvagapov          #+#    #+#             */
/*   Updated: 2022/12/27 15:00:54 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Looks for a newline character in buffer starting from start_index.
// Returns the index of the character folowing the newline.
// Returns 0 is no newline was found.
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

// Returns the length of the string s
size_t	ft_strlen(const char *s)
{
	size_t	res;

	res = 0;
	while (s[res])
		res++;
	return (res);
}

// Initialises res as an empty string.
// In case of success returns 1.
// In case of error (malloc fail) returns 0.
int	init_res(char **res)
{
	*res = (char *)malloc(sizeof(char) * 1);
	if (!*res)
		return (0);
	(*res)[0] = '\0';
	return (1);
}
