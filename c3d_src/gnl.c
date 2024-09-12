/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njeanbou <njeanbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:21:18 by njeanbou          #+#    #+#             */
/*   Updated: 2024/09/06 02:42:19 by njeanbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../c3d_inc/cub3d.h"



char	*gnl(int fd, char *buffer)
{
	int		index;
	int		bytes;
	char	character;

	if (fd < 0)
		return (NULL);
	index = 0;
	bytes = read(fd, &character, 1);
	while (bytes > 0)
	{
		buffer[index++] = character;
		if (character == '\n')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (NULL);
	buffer[index] = '\0';
	return (buffer);
}

char	*gnl_map(int fd, char *buffer)
{
	int		index;
	int		bytes;
	char	character;

	if (fd < 0)
		return (NULL);
	index = 0;
	bytes = read(fd, &character, 1);
	while (bytes > 0)
	{
		buffer[index++] = character;
		if (character == '\0')
			break ;
		bytes = read(fd, &character, 1);
	}
	if ((bytes <= 0) && (index == 0))
		return (NULL);
	buffer[index] = '\0';
	return (buffer);
}